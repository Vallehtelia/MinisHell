/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/24 18:29:05 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = 0;

int	main(void)
{
	char		*input;
	t_minishell	mshell;

	mshell = (t_minishell){};
	printf("\033[2J\033[H"); // clears screen
	while (1)
	{
		matti_set(&mshell);
		input = readline(mshell.input_cmd);
		if (!input)
			break ;
		free_workingdir(&mshell);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			exit_and_free(&mshell, 0);
			break ;
		}
		mshell.input_cmd = input;
		matti(&mshell);
		valle(&mshell);
		add_history(input);
		free(input);
	}
	return (0);
}
