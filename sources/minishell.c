/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/02 19:57:51 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = 0;

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	mshell;

	(void)ac;
	(void)av;
	mshell = (t_minishell){};

	// print_shrek();
	mshell.env = parse_env(envp, -1, 0);
	delete_env(&mshell, "OLDPWD");
	handle_signal();
	while (1)
	{
		//signal(SIGQUIT, sigquit_handler); // jatan viela tahan, jos tarvii myohemmin
		matti_set(&mshell);
		input = readline(mshell.prompt_text);
		if (!input)
			break ;
		free_workingdir(&mshell);
		count_pipes(&mshell, input, 0, false);
		if (mshell.ends_with_pipe == true)
			handle_pipe_end(&mshell, input);
		else
			mshell.input_cmd = input;
		matti(&mshell);
		valle(&mshell);
		add_history(mshell.input_cmd);
		free(input);
	}
	return (0);
}
