/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 21:48:46 by vvaalant         ###   ########.fr       */
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
	execute_cmd(mshell, mshell->cmds[i]->cmd, mshell->env);
}

static void	parent_process(t_minishell *mshell, int i, int fd_in, int *pipefd)
{
	int	status;
	int	trash;

	if (fd_in != 0)
		close(fd_in);
	if (mshell->cmds[i + 1])
	{
		trash = 0;
		while (trash < 100000)
			trash++;
		close(pipefd[1]);
		run_commands(mshell, i + 1, pipefd[0]);
	}
	waitpid(mshell->last_pid, &status, 0);
	if (WIFEXITED(status))
		mshell->exit_code = WEXITSTATUS(status);
	signal_basic();
}

void	run_commands(t_minishell *mshell, int i, int fd_in)
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
		mshell->last_pid = fork();
		if (mshell->last_pid == 0)
		{
			child_process(mshell, i, fd_in, pipefd);
		}
		else
		{
			parent_process(mshell, i, fd_in, pipefd);
			if (mshell->cmds[i + 1])
				close(pipefd[0]);
		}
	}
}

