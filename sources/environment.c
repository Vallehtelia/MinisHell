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
	env_var->key = key;
	env_var->value = value;
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

t_env	** add_env(t_minishell *mshell, char *key, char *value) // Taytta paskaa. Ei toimi!!!!!
{
	int	i;
	int env_count;
	t_env	**temp_env_vars;

	i = 0;
	env_count = 0;
	while (mshell->env[env_count])
		env_count++;
	temp_env_vars = malloc(sizeof(t_env *) * (env_count + 2));
	if (!temp_env_vars)
		return NULL; // Joku kunnon malloc check tähän
	while (mshell->env[i])
	{
		temp_env_vars[i] = allocate_env(mshell->env[i]->key, mshell->env[i]->value);
		//printf(" OLD key: %s value: %s\n", mshell->env[i]->key, mshell->env[i]->value);
		//printf(" NEW key: %s value: %s\n", temp_env_vars[i]->key, temp_env_vars[i]->value);
		i++;

	}
	//free_env(mshell);
	temp_env_vars[i] = allocate_env(key, value);
	//printf(" OLD key: %s value: %s\n", mshell->env[i]->key, mshell->env[i]->value);
	temp_env_vars[i + 1] = NULL;
	//printf(" OLD key: %s value: %s\n", mshell->env[i +1 ]->key, mshell->env[i + 1]->value);
	return (temp_env_vars);
	//i = 0;
	//
	//mshell->env = malloc(sizeof(t_env *) * (env_count + 2));
	//while (temp_env_vars[++i])
	//{
	//	mshell->env[i] = allocate_env(temp_env_vars[i]->key, temp_env_vars[i]->value);
	//}
	//temp_env_vars[i] = allocate_env(key, value);
	//temp_env_vars[i + 1] = NULL;
	////printf(" OLD key: %s value: %s\n", mshell->env[i]->key, mshell->env[i]->value);
	////printf(" NEW key: %s value: %s\n", temp_env_vars[i]->key, temp_env_vars[i]->value);
	////free_env(mshell);
	////printf("TESTI\n");

	//mshell->env = temp_env_vars;
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
			if(!ft_strncmp(key, "OLDPWD", 6)) // Jattaa OLDPWD pois. Pitaa ehka keksia parempi tapa
				continue;
			value = ft_strdup(del_pos + 1);
			env_vars[i] = allocate_env(key, value);
		}
		else
			env_vars[i] = NULL;
	}
	env_vars[i] = NULL;
	return (env_vars);
}
