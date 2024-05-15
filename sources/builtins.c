/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:10:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 18:52:30 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_pwd(t_minishell *mshell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("minishell: pwd: error retrieving current directory\n");
		mshell->exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
		mshell->exit_code = 0;
	}
}

static int	check_exit(t_minishell *mshell, char **cmd)
{
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		if (run_exit(mshell, cmd, 0, 0))
			return (1);
	}
	return (0);
}

int	check_builtins(t_minishell *mshell, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		if (echo(mshell, cmd, 1))
			return (0);
		return (1);
	}
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		get_pwd(mshell);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
	{
		print_env(mshell);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
	{
		if (cmd[1] == NULL)
			print_env_export(mshell);
		return (1);
	}
	else if (check_exit(mshell, cmd))
		return (1);
	return (0);
}
