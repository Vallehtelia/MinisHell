/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/11 20:38:16 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = DEFAULT;

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	mshell;

	(void)ac;
	(void)av;
	mshell = (t_minishell){};

	// print_shrek();
	mshell.env = parse_env(envp, -1);
	delete_env(&mshell, "OLDPWD");
	while (1)
	{
		signal_basic();
		matti_set(&mshell);
		input = readline(mshell.prompt_text);
		if (!input)
		{
			printf("exit\n");
			exit_and_free(&mshell, 0);
		}
		free_workingdir(&mshell);
		count_pipes(&mshell, input, 0, false);
		if (mshell.ends_with_pipe == true)
		{
			if(handle_pipe_end(&mshell, input))
			{
				add_history(input);
				mshell.num_of_pipes = 0;
				free(input);
				continue ;
			}
		}
		else
			mshell.input_cmd = input;
		valle(&mshell);
		add_history(mshell.input_cmd);
		free(input);
	}
	return (0);
}
