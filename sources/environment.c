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
