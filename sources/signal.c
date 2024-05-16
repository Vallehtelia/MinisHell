/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:37:28 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/15 17:36:56 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	1 = caret is on
	0 = caret is off
*/
void	caret_switch(int on)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
	Signal handler for basic shell
	- SIGINT is set to handle_sigint()
	- SIGQUIT is set to ignore
*/
void	signal_basic(void)
{
	caret_switch(0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/*
	Signal handler before executing commands
	- Ignores SIGINT and SIGQUIT
*/
void	signal_execute(void)
{
	caret_switch(0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*
	Puts the signals back to default
*/
void	signal_default(void)
{
	caret_switch(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
