/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:10:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/15 14:29:05 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo(t_minishell *mshell, char **cmd, int i)
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
	mshell->exit_code = 0;
}

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
		ft_printf("%s\n", pwd);
		free(pwd);
		mshell->exit_code = 0;
	}
}

void	run_exit(t_minishell *mshell, char **cmd)
{
	if (cmd[1] != NULL)
	{
		ft_printf("minishell: exit: too many arguments\n");
		mshell->exit_code = 1;
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
				error_str(mshell, mshell->cmds[0]->cmd[0], 2);
			else if (statbuf.st_mode & S_IXUSR)
				execute_cmd(mshell, mshell->cmds[0]->cmd, mshell->env);
			else
				error_str(mshell, mshell->cmds[0]->cmd[0], 3);
		}
		else
			error_str(mshell, mshell->cmds[0]->cmd[0], 1);
	}
	else
		error_str(mshell, mshell->cmds[0]->cmd[0], 4);
}

void print_env(t_env **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s=%s\n", env[i]->key, env[i]->value);
		i++;
	}
}

int	check_builtins(t_minishell *mshell, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		echo(mshell, cmd, 1);
		return (1);
	}
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		get_pwd(mshell);
		return (1);
	}
	if (check_exit_code(mshell, cmd))
	{
		return (1);
	}
	else if (cmd[0][0] == '$' && cmd[0][1] != '\0')
	{
		handle_env_var(mshell);
		return (1);
	}
	else if(ft_strncmp(cmd[0], "env", 4) == 0)
	{
		print_env(mshell->env);
		return (1);
	}
	return (0);
}
