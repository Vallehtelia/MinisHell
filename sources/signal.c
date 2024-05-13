/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrinkine <mrinkine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:37:28 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/13 14:37:31 by mrinkine         ###   ########.fr       */
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

/*
	Signal handler before executing commands
	- Ignores SIGINT and SIGQUIT
*/
void	signal_execute(void)
{
	caret_switch(1);
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
