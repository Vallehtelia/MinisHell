/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:37:42 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/15 17:37:33 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_sig_exec(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
}

static void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(1);
	}
}

/*
	Signal handler for heredoc
	- SIGINT is set to handle_sigint_heredoc()
	- SIGQUIT is set to ignore
*/
void	signal_heredoc(void)
{
	caret_switch(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/*
	Signal handler for executing commands
	- SIGINT is set to ignore
	- SIGQUIT is set to sigquit_handler()
*/
void	signal_in_execve(void)
{
	caret_switch(1);
	signal(SIGINT, handle_sig_exec);
	signal(SIGQUIT, sigquit_handler);
}
