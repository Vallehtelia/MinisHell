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

	mshell.num_of_pipes = 1;
	//valle_set(&mshell);
	while (1)
	{
		matti_set(&mshell);
		printf("\033[1;32mC:%s\\> \033[0m",mshell.working_directory);
		input = readline("");//(const char *)
		if (!input)
			break ;
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			exit_and_free(&mshell, 0);
			break ;
		}
		mshell.input_cmd = input;
		valle(&mshell);
		matti(&mshell);
		// useinput(&mshell);
		//parse_command(&mshell);
		add_history(input);
		free(input);
	}
	return (0);
}
