/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:38:04 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 01:43:32 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	builtin_check(t_minishell *mshell, int i)
{
	if (ft_strncmp(mshell->cmds[i]->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "exit", 5) == 0)
		return (1);
	return (0);
}

char	*change_value_value(char *cmd, char *value, int j, int k)
{
	char	*temp;
	char	*temp_two;

	temp = ft_strndup(cmd, k);
	temp_two = ft_strjoin(temp, value);
	free(temp);
	temp = ft_strjoin(temp_two, cmd + j);
	free(temp_two);
	return (temp);
}

static int	check_single_quote(t_minishell *mshell, int i, int *l)
{
	if (mshell->cmds[i]->cmd[*l][0] == '\'')
	{
		(*l)++;
		return (1);
	}
	return (0);
}

static int	close_spaces(t_minishell *mshell, int i, int l)
{
	int		move_index;

	free(mshell->cmds[i]->cmd[l]);
	move_index = l;
	while (mshell->cmds[i]->cmd[move_index + 1])
	{
		mshell->cmds[i]->cmd[move_index] = mshell->cmds[i]->cmd[move_index + 1];
		move_index++;
	}
	mshell->cmds[i]->cmd[move_index] = NULL;
	if (mshell->cmds[i]->cmd[l] == NULL)
		return (1);
	return (0);
}

int	handle_values(t_minishell *mshell, int i, int l, int cmd_check)
{
	while (mshell->cmds[++i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l] != NULL)
		{
			cmd_check = builtin_check(mshell, i);
			if (check_single_quote(mshell, i, &l))
				continue ;
			if (check_exit_code(mshell, i, l))
				return (1);
			if (change_value(mshell, i, l, cmd_check))
				return (1);
			if (mshell->cmds[i]->cmd[l]
				&& ft_strlen(mshell->cmds[i]->cmd[l]) == 0)
			{
				if (close_spaces(mshell, i, l))
					break ;
			}
			l++;
		}
	}
	if (mshell->cmds[0]->cmd[0] == NULL)
		return (1);
	return (0);
}
