/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/25 13:30:40 by vvaalant         ###   ########.fr       */
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

	print_shrek();
	mshell.env = parse_env(envp, -1, 0);
	delete_env(&mshell, "OLDPWD");
	while (1)
	{
		//signal(SIGQUIT, handle_sigquit); // Commented out to help debugging
		//signal_handler(&mshell);
		matti_set(&mshell);
		input = readline(mshell.prompt_text);
		if (!input)
			break ;
		free_workingdir(&mshell);
		count_pipes(&mshell, input);
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
