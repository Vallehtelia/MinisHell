/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/05 18:14:22 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = 0;

// int	hardcode(t_minishell *mshell, char *input)
// {
// 	if (ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
// 	{
// 		free(input);
// 		exit_and_free(mshell, 0);
// 	}
// 	if (ft_strncmp(input, "$?", 3) == 0)
// 	{
// 		add_history(input);
// 		free(input);
// 		printf("minisHell: %d: command not found\n", global_signal);
// 		global_signal = 127;
// 		return (1);
// 	}
// 	return (0);
// }



int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	mshell;

	(void)ac;
	(void)av;
	mshell = (t_minishell){};

	//av = NULL;
	//ac = 0;
	print_shrek();
	mshell.env = parse_env(envp, -1, 0);
	while (1)
	{
		matti_set(&mshell);
		input = readline(mshell.prompt_text);
		if (!input)
			break ;
		free_workingdir(&mshell);
		// if(hardcode(&mshell, input))
		// 	continue ;
		mshell.input_cmd = input;
		matti(&mshell);
		valle(&mshell);
		//printf("KUMMAN VIKA!!!\n");
		add_history(input);
		free(input);
	}
	return (0);
}
