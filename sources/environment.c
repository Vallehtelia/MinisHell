/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:11:36 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 17:45:47 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*allocate_env(char *key, char *value, int parsing)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (NULL);
	env_var->key = ft_strdup(key);
	env_var->value = ft_strdup(value);
	if (parsing == 1)
		env_var->have_value = true;
	return (env_var);
}

int	env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

bool	check_if_env_exists(t_env **env, char *key)
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
int	set_env_value(t_env **env, char *key, char *value, int i)
{
	char	*cleaned_value;

	while (env[++i])
	{
		if (ft_strncmp(env[i]->key, key, ft_strlen(key) + 1) == 0)
		{
			if (env[i]->value)
				free(env[i]->value);
			cleaned_value = clean_value(value, 0, 0);
			if (!cleaned_value)
				return (1);
			env[i]->value = ft_strdup(cleaned_value);
			if (!env[i]->value)
			{
				free(cleaned_value);
				return (1);
			}
			if (cleaned_value)
				free(cleaned_value);
			env[i]->have_value = true;
			return (0);
		}
	}
	return (1);
}

int	parse_quotes(char *string)
{
	int		len;
	int		i;
	char	current_quote;

	i = 0;
	len = 0;
	current_quote = '\0';
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '\"') && current_quote == 0)
			current_quote = string[i++];
		else if (string[i] == current_quote)
		{
			current_quote = 0;
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
