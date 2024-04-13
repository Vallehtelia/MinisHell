/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:10:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/13 20:44:28 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo(char **cmd, int i)
{
	if (!cmd[i])
		ft_printf("\n");
	else if (ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		while (ft_strncmp(cmd[i], "-n", 3) == 0)
			i++;
		while (cmd[i] != NULL)
		{
			if (cmd[i + 1] == NULL)
				ft_printf("%s", cmd[i]);
			else
				ft_printf("%s ", cmd[i]);
			i++;
		}
	}
	else
	{
		while (cmd[i] != NULL)
		{
			ft_printf("%s ", cmd[i]);
			i++;
		}
		ft_printf("\n");
	}
	global_signal = 0;
}

static void	get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("minishell: pwd: error retrieving current directory\n");
		global_signal = 1;
	}
	else
	{
		ft_printf("%s\n", pwd);
		free(pwd);
		global_signal = 0;
	}
}

void	run_exit(t_minishell *mshell, char **cmd)
{
	if (cmd[1] != NULL)
	{
		ft_printf("minishell: exit: too many arguments\n");
		global_signal = 1;
		return ;
	}
	else
	{
		ft_printf("exit\n");
		exit_and_free(mshell, 0);
	}
}

static void	handle_env_var(t_minishell *mshell)
{
	struct stat	statbuf;
	char		*value;

	value = get_env_value(mshell->env, mshell->cmds[0]->cmd[0] + 1);
	if (value != NULL)
	{
		free(mshell->cmds[0]->cmd[0]);
		mshell->cmds[0]->cmd[0] = ft_strdup(value);
		if (stat(mshell->cmds[0]->cmd[0], &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				error_str(mshell->cmds[0]->cmd[0], 2);
			else if (statbuf.st_mode & S_IXUSR)
				execute_cmd(mshell, mshell->cmds[0]->cmd, mshell->env);
			else
				error_str(mshell->cmds[0]->cmd[0], 3);
		}
		else
			error_str(mshell->cmds[0]->cmd[0], 1);
	}
	else
		error_str(mshell->cmds[0]->cmd[0], 4);
}

int	check_builtins(t_minishell *mshell, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		echo(cmd, 1);
		return (1);
	}
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		get_pwd();
		return (1);
	}
	if (check_exit_code(cmd))
	{
		return (1);
	}
	else if (cmd[0][0] == '$' && cmd[0][1] != '\0')
	{
		handle_env_var(mshell);
		return (1);
	}
	return (0);
}
