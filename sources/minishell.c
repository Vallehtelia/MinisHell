/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 20:50:30 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_init(int ac, char **av, char **envp, t_minishell *mshell)
{
	if (ac != 1 || !av || !envp || !mshell)
	{
		printf("Error: Start minisHell with no arguments\n");
		exit(1);
	}
	mshell->env = parse_env(envp, -1);
	delete_env(mshell, "OLDPWD");
	//signal_basic();
	// print_shrek();
}

void	eof_exit(t_minishell *mshell, char *input)
{
	(void)mshell;
	free(input);
	printf("exit\n");
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	mshell;

	mshell = (t_minishell){};
	ms_init(ac, av, envp, &mshell);
	while (1)
	{
		matti_set(&mshell);
		input = readline(mshell.prompt_text);
		if (!input)
			eof_exit(&mshell, input);
		free_workingdir(&mshell);
		count_pipes(&mshell, input, 0, false);
		if (mshell.ends_or_starts_with_pipe == true)
		{
			handle_pipe_end(&mshell, input);
			continue ;
		}
		else
			mshell.input_cmd = input;
		valle(&mshell);
		add_history(mshell.input_cmd);
		free(input);
	}
	return (0);
}
