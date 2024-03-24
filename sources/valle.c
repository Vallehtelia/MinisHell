/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/22 15:28:26 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_command(t_minishell *mshell)
{
	printf("%i\n", mshell->num_of_pipes);
	mshell->num_of_pipes++;
}

void valle(t_minishell *mshell)
{
	parse_command(mshell);
}
