/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:26:41 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:27:56 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_env_var(t_minishell *mshell, char *env)
{
	struct stat	statbuf;

	if (stat(env, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			error_str(mshell, env, ": is a directory", 2);
		else if (statbuf.st_mode & S_IXUSR)
			return (0);
		else
			error_str(mshell, env, ": permission denied", 1);
		return (1);
	}
	else
	{
		error_str(mshell, env, ": command not found", 1);
		return (1);
	}
	return (0);
}

void	print_env(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->env[i])
	{
		if (mshell->env[i]->have_value)
		{
			printf("%s=%s\n", mshell->env[i]->key, mshell->env[i]->value);
		}
		i++;
	}
}

void	print_env_export(t_minishell *mshell)
{
	int		i;
	char	abc;

	i = 0;
	abc = 'A';
	while (abc <= 'z')
	{
		while (mshell->env[i])
		{
			if (mshell->env[i]->key[0] == abc)
			{
				if (mshell->env[i]->have_value)
					printf("declare -x %s=\"%s\"\n", \
					mshell->env[i]->key, mshell->env[i]->value);
				else
					printf("declare -x %s\n", mshell->env[i]->key);
			}
			i++;
		}
		abc++;
		i = 0;
	}
}

bool	check_indentifier(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (false);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
