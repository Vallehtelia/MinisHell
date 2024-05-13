/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrinkine <mrinkine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:37:42 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/13 14:37:45 by mrinkine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	//rl_replace_line("", 0);
	printf("Quit: 3\n");
	//rl_on_new_line();
	//rl_redisplay();
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_handler);
}


