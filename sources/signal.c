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
void	sigquit_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	rl_on_new_line();
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
/*
	Signal handler for basic shell
	- SIGINT is set to handle_sigint()
	- SIGQUIT is set to ignore
*/
void	signal_basic(void)
{
	//printf("--Signal basic pid: %i--\n", getpid());
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	caret_switch(0);
	signal(SIGINT,handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
/*
	Signal handler before executing commands
	- Ignores SIGINT and SIGQUIT
*/
void	signal_execute(void)
{
	//printf("--Signal execute pid: %i--\n", getpid());
	caret_switch(1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
/*
	Signal handler for heredoc
	- SIGINT is set to handle_sigint_heredoc()
	- SIGQUIT is set to ignore
*/
void	signal_heredoc(void)
{
	//printf("--Signal heredoc pid: %i--\n", getpid());
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
	//printf("--Signal in_exevce pid: %i--\n", getpid());
	caret_switch(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_handler);
}
/*
	Puts the signals back to default
*/
void	signal_default(void)
{
	//printf("--Signal defaul pid: %i--\n", getpid());
	caret_switch(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

