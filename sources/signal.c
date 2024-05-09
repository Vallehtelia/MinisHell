#include "../includes/minishell.h"

/*
1 = caret is on
0 = caret is off
*/
void    caret_switch(int on)
{
    struct termios    term;

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

static void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(1);
	}
}

void	signal_basic(void)
{
	caret_switch(0);
	signal(SIGINT,handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_execute(int child_pid)
{
	(void)child_pid;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(int child_pid)
{
	caret_switch(0);
	signal(SIGINT, SIG_DFL);
	if (child_pid == 0)
		signal(SIGINT, handle_sigint_heredoc);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

