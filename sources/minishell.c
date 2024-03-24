/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/24 16:30:08 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = 0;

int	main(void)
{
	char		*input;
	t_minishell	mshell;

	mshell.num_of_pipes = 1;
	while (1)
	{
		input = readline(GREEN"Shrek is love, Shrek is life--> "DEFAULT);
		if (!input)
			break ;
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
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
