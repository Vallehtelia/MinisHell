#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

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

void	sigquit_handler(int sig) // Ei kaytossa, mutta saatttaa tarvita myohemmin
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
int	handle_signal(void)
{
	caret_switch(0);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}


//void print_prompt(t_minishell *mshell)
//{
//	printf("%s",mshell->prompt_text);
//}

//void handle_sigint(int sig)
//{
//	(void)sig;
//	write(1, "\n", 1);
//}

//void handle_sigquit(int sig)
//{
//	(void)sig;
//	write(1, "exit\n", 5);
//}
//void signal_handler(t_minishell *mshell)
//{
//	(void)mshell;
//	signal(SIGINT, handle_sigint);
//	//signal(SIGQUIT, handle_sigquit);

//}
