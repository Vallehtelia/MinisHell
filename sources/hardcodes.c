/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:50:13 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/05 16:54:13 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd(t_minishell *mshell)
{
	if ((ft_strncmp(mshell->cmds[0]->cmd[0], "exit", 5) == 0)
		&& mshell->cmds[0]->cmd[1] == NULL)
	{
		exit_and_free(mshell, 0);
		return (1);
	}
	if ((ft_strncmp(mshell->cmds[0]->cmd[0], "exit", 5) == 0)
		&& mshell->cmds[0]->cmd[1] != NULL)
	{
		ft_printf("minisHell: exit: too many arguments\n");
		global_signal = 1;
		return (1);
	}
	if (ft_strncmp(mshell->cmds[0]->cmd[0], "$?", 3) == 0)
	{
		ft_printf("minisHell: %d: command not found\n", global_signal);
		global_signal = 127;
		return (1);
	}
	return (0);
}