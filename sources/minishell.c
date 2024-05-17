/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/17 18:14:33 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_init(int ac, char **av, char **envp, t_minishell *mshell)
{
	print_shrek();
	mshell->free_last_pid = false;
	if (ac != 1 || !av || !envp || !mshell)
	{
		printf("Error: Start minisHell with no arguments\n");
		exit(1);
	}
	mshell->env = parse_env(envp, -1);
	delete_env(mshell, "OLDPWD");
}

void	eof_exit(t_minishell *mshell, char *input)
{
	(void)mshell;
	free(input);
	printf("exit\n");
	exit(0);
}

static bool	main_loop_helper(t_minishell *mshell, char *input)
{
	if (!input)
		eof_exit(mshell, input);
	free_workingdir(mshell);
	count_pipes(mshell, input, 0, false);
	if (mshell->ends_or_starts_with_pipe == true)
	{
		handle_pipe_end(mshell, input);
		return (true);
	}
	else
		mshell->input_cmd = input;
	return (false);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	mshell;

	mshell = (t_minishell){};
	ms_init(ac, av, envp, &mshell);
	while (1)
	{
		loop_set(&mshell);
		input = readline(mshell.prompt_text);
		if (main_loop_helper(&mshell, input) == true)
			continue ;
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		loop_exc(&mshell);
		add_history(mshell.input_cmd);
		free(input);
	}
	return (0);
}
