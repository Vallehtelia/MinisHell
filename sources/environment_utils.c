/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:42:05 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 17:43:38 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_value(char *value, int i, int x)
{
	char	*cleaned_value;
	char	current_quote;

	cleaned_value = malloc(sizeof(char) * (parse_quotes(value) + 1));
	if (!cleaned_value)
		return (NULL);
	current_quote = '\0';
	while (value[i])
	{
		if ((value[i] == '\'' || value[i] == '\"') && current_quote == '\0')
		{
			current_quote = value[i];
			i++;
			while (value[i] != current_quote && value[i] != '\0')
				cleaned_value[x++] = value[i++];
			if (value[i] == current_quote)
				i++;
			current_quote = '\0';
		}
		else
			cleaned_value[x++] = value[i++];
	}
	cleaned_value[x] = '\0';
	return (cleaned_value);
}

void	add_env(t_minishell *mshell, char *key, char *value)
{
	int		i;
	int		env_count;
	t_env	**temp_env_vars;

	i = 0;
	env_count = 0;
	while (mshell->env[env_count])
		env_count++;
	temp_env_vars = malloc(sizeof(t_env *) * (env_count + 2));
	if (!temp_env_vars)
		return ;
	while (mshell->env[i])
	{
		temp_env_vars[i] = allocate_env(mshell->env[i]->key, \
		mshell->env[i]->value, 1);
		i++;
	}
	if (ft_strlen(value) == 0)
		temp_env_vars[i] = allocate_env(key, value, 0);
	else
		temp_env_vars[i] = allocate_env(key, value, 1);
	temp_env_vars[i + 1] = NULL;
	free_env(mshell);
	mshell->env = NULL;
	mshell->env = temp_env_vars;
}

void	delete_env(t_minishell *mshell, char *key)
{
	int		i;
	int		x;
	int		env_count;
	t_env	**te;

	i = -1;
	x = 0;
	env_count = 0;
	if (!check_if_env_exists(mshell->env, key))
		return ;
	while (mshell->env[env_count])
		env_count++;
	te = malloc(sizeof(t_env *) * (env_count));
	while (mshell->env[++i])
	{
		if (ft_strncmp(mshell->env[i]->key, key, ft_strlen(key) + 1) != 0)
		{
			te[x] = allocate_env(mshell->env[i]->key, mshell->env[i]->value, 1);
			x++;
		}
	}
	te[x] = NULL;
	free_env(mshell);
	mshell->env = NULL;
	mshell->env = te;
}

void	parse_env_helper(t_env **env_vars, char *env_entry, char *del_po, int i)
{
	char	*key;
	char	*value;
	int		keylen;

	keylen = del_po - env_entry;
	key = ft_strndup(env_entry, keylen);
	value = ft_strdup(del_po + 1);
	env_vars[i] = allocate_env(key, value, 1);
	free (key);
	free (value);
}

t_env	**parse_env(char **envp, int i)
{
	t_env	**env_vars;
	char	*env_entry;
	char	*del_pos;

	env_vars = malloc(sizeof(t_env *) * (env_count(envp) + 1));
	if (!env_vars)
		return (NULL);
	while (envp[++i])
	{
		env_entry = envp[i];
		del_pos = ft_strchr(envp[i], '=');
		if (del_pos)
			parse_env_helper(env_vars, env_entry, del_pos, i);
		else
			env_vars[i] = NULL;
	}
	env_vars[i] = NULL;
	return (env_vars);
}
