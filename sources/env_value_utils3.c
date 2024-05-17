/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:26:41 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/17 18:52:15 by vvaalant         ###   ########.fr       */
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
		return (0);
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
	mshell->exit_code = 0;
}

void	print_env_export(t_minishell *mshell)
{
	t_tempsort	*head;
	t_tempsort	*tmp;

	head = create_list(mshell);
	if (!head)
	{
		mshell->exit_code = 1;
		return ;
	}
	sort_list(head, NULL, NULL, false);
	tmp = head;
	while (head)
	{
		if (head->have_value)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
	free_list(tmp);
	mshell->exit_code = 0;
	return ;
}

bool	check_indentifier(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_' && key[i] != '/')
		return (false);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '/')
			return (false);
		i++;
	}
	return (true);
}

void	export_env_pwd(t_minishell *mshell, char **cmd, int i)
{
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	value = getcwd(NULL, 0);
	if (handle_identifier(mshell, key, value, 1))
	{
		error_str(mshell, "export :", cmd[i], 3);
		mshell->exit_code = 1;
	}
	mshell->cd_dot_used = 0;
}
