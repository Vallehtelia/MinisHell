/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:11:36 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/28 08:05:04 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*allocate_env(char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (NULL);
	env_var->key = ft_strdup(key);
    env_var->value = ft_strdup(value);
	return (env_var);
}

static int	env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
bool check_if_env_exists(t_env **env, char *key)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i]->key, key, ft_strlen(key) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}
/*
	Changes value of environment variable.
*/
int		set_env_value(t_env **env, char *key, char* value)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i]->key, key, ft_strlen(key) + 1) == 0)
		{
			if(ft_strlen(env[i]->value) > 0)
				free(env[i]->value);
			env[i]->value = NULL;
			env[i]->value = ft_strdup(value);
			if(!env[i]->value)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

void add_env(t_minishell *mshell, char *key, char *value)
{
	int i;
    int env_count;
    t_env **temp_env_vars;

	i = 0;
    env_count = 0;
	if(check_if_env_exists(mshell->env, key))
	{
		set_env_value(mshell->env, key, value);
		return;
	}
    while (mshell->env[env_count])
        env_count++;
    temp_env_vars = malloc(sizeof(t_env *) * (env_count + 2));
    while (mshell->env[i])
    {
        temp_env_vars[i] = allocate_env(mshell->env[i]->key, mshell->env[i]->value);
        i++;
    }
    temp_env_vars[i] = allocate_env(key, value);
	temp_env_vars[i + 1] = NULL;
    free_env(mshell);
	mshell->env = NULL;
    mshell->env = temp_env_vars;
}

void	delete_env(t_minishell *mshell, char *key)
{
	int i;
	int x;
	int env_count;
	t_env **temp_env_vars;

	i = 0;
	x = 0;
	env_count = 0;
	if(!check_if_env_exists(mshell->env, key))
		return;
	while (mshell->env[env_count])
		env_count++;
	temp_env_vars = malloc(sizeof(t_env *) * (env_count));
	while (mshell->env[i])
	{
		if(ft_strncmp(mshell->env[i]->key, key, ft_strlen(key) + 1) != 0)
		{
			temp_env_vars[x] = allocate_env(mshell->env[i]->key, mshell->env[i]->value);
			x++;
		}
		i++;
	}
	temp_env_vars[i] = NULL;
    free_env(mshell);
	mshell->env = NULL;
	mshell->env = temp_env_vars;
}


t_env	**parse_env(char **envp, int i, int keylen)
{
	t_env	**env_vars;
	char	*env_entry;
	char	*del_pos;
	char	*key;
	char	*value;

	env_vars = malloc(sizeof(t_env *) * (env_count(envp) + 1));
	if (!env_vars)
		return (NULL);
	while (envp[++i])
	{
		env_entry = envp[i];
		del_pos = ft_strchr(envp[i], '=');
		if (del_pos)
		{
			keylen = del_pos - env_entry;
			key = ft_strndup(env_entry, keylen);
			value = ft_strdup(del_pos + 1);
			env_vars[i] = allocate_env(key, value);
		}
		else
			env_vars[i] = NULL;
	}
	env_vars[i] = NULL;
	return (env_vars);
}
