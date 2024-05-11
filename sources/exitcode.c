/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:32:36 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 01:35:42 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_code_helper_two(t_minishell *mshell, char *temp, int i, int l)
{
	free(mshell->cmds[i]->cmd[l]);
	mshell->cmds[i]->cmd[l] = temp;
	return ;
}

static int	check_new_cmd(char *new_cmd, char *temp_two)
{
	if (!new_cmd)
	{
		free(temp_two);
		return (1);
	}
	return (0);
}

static int	exit_code_helper(t_minishell *mshell, char *temp, int i, int l)
{
	char	*temp_two;
	char	*new_cmd;
	char	*new_cmd_two;

	temp_two = ft_strndup(mshell->cmds[i]->cmd[l], \
		temp - mshell->cmds[i]->cmd[l]);
	if (!temp_two)
		return (1);
	new_cmd_two = ft_itoa(mshell->exit_code);
	new_cmd = ft_strjoin(temp_two, new_cmd_two);
	free(new_cmd_two);
	if (check_new_cmd(new_cmd, temp_two))
		return (1);
	if (temp + 2)
	{
		exit_code_helper_two(mshell, ft_strjoin(new_cmd, temp + 2), i, l);
		free(new_cmd);
	}
	else
	{
		free(mshell->cmds[i]->cmd[l]);
		mshell->cmds[i]->cmd[l] = new_cmd;
	}
	free(temp_two);
	return (0);
}

int	check_exit_code(t_minishell *mshell, int i, int l)
{
	char	*temp;

	temp = NULL;
	temp = ft_strchr(mshell->cmds[i]->cmd[l], '$');
	if (temp)
	{
		if (ft_strncmp(temp, "$?", 2) == 0)
		{
			if (exit_code_helper(mshell, temp, i, l))
				return (1);
		}
	}
	return (0);
}
