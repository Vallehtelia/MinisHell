/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/13 21:04:25 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = 0;

int	main(void)
{
	char	*input;

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
		add_history(input);
		free(input);
	}
	return (0);
}
