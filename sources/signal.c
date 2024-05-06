#include "../includes/minishell.h"

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
void	sigint_handler(int sig)
{
	//(void)sig;
	//printf("\nSINGNAALI !! sig = %d global = %d\n",sig, global_signal);
	if(sig == SIGINT && global_signal == DEFAULT)
	{
		caret_switch(0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		global_signal = DEFAULT;
		return ;
	}
	if(sig == SIGINT && global_signal == IN_HEREDOC)
	{
		caret_switch(0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		global_signal = DEFAULT;
		return ;
	}
	if(global_signal == 0)
	{
		caret_switch(0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		global_signal = DEFAULT;
		return ;
	}
	//printf("\nTULEEKO TANNE KOSKAAAN!!!\n");
	global_signal = sig;
	caret_switch(0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();

	//if (global_signal != IN_HEREDOC)
	//	ft_putstr_fd("\n", STDERR_FILENO);
	//if (global_signal == IN_CMD)
	//{
	//	//global_signal = STOP_HEREDOC;
	//	rl_replace_line("", 0);
	//	rl_redisplay();
	//	//rl_done = 1;
	//	return ;
	//}
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
	//(void) sig;
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
