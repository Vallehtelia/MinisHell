/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/17 18:22:35 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(t_minishell *mshell, int i, int fd_in, int *pipefd)
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (mshell->cmds[i + 1])
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	signal_in_execve();
	execute_cmd(mshell, mshell->cmds[i]->cmd, mshell->env);
}

static void	signal_check_helper(t_minishell *mshell, int status)
{
	if (status == 2)
	{
		ft_putstr_fd("^C\n", STDOUT_FILENO);
		mshell->exit_code = 130;
	}
	else if (status == 3)
	{
		ft_putstr_fd("^\\Quit: 3\n", STDOUT_FILENO);
		mshell->exit_code = 131;
	}
}

static void	signal_check(t_minishell *mshell, int status, int i)
{
	if (mshell->num_of_cmds > 1)
	{
		if (i == 0)
		{
			if (status == 2)
			{
				ft_putstr_fd("^C\n", STDOUT_FILENO);
				mshell->exit_code = 130;
			}
			else if (status == 3)
			{
				ft_putstr_fd("^\\", STDOUT_FILENO);
				mshell->exit_code = 131;
			}
		}
		return ;
	}
	else if (i == 0)
		signal_check_helper(mshell, status);
}

static void	parent_process(t_minishell *mshell, int i, int fd_in, int *pipefd)
{
	int	status;
	int	trash;

	status = 0;
	if (fd_in != 0)
		close(fd_in);
	if (mshell->cmds[i + 1])
	{
		trash = 0;
		while (trash < 100000)
			trash++;
		close(pipefd[1]);
		run_commands(mshell, i + 1, pipefd[0], i + 1);
	}
	waitpid(mshell->last_pid[i], &status, 0);
	if (WIFEXITED(status) && i == mshell->num_of_cmds - 1)
		mshell->exit_code = WEXITSTATUS(status);
	signal_check(mshell, status, i);
	signal_ignore();
}

void	run_commands(t_minishell *mshell, int i, int fd_in, int pid_index)
{
	int	pipefd[2];

	if (mshell->cmds[i])
	{
		if (mshell->cmds[i + 1])
		{
			if (pipe(pipefd) == -1)
			{
				ft_putstr_fd("minisHell: pipe error\n", 2);
				mshell->exit_code = 1;
				return ;
			}
		}
		signal_ignore();
		mshell->last_pid[pid_index] = fork();
		if (mshell->last_pid[pid_index] == 0)
			child_process(mshell, i, fd_in, pipefd);
		else
		{
			parent_process(mshell, i, fd_in, pipefd);
			if (mshell->cmds[i + 1])
				close(pipefd[0]);
		}
	}
}
