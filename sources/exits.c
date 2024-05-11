/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:28:29 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:30:04 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exit_helper(char **cmd, int i, int res, int neg)
{
	char	*temp;

	temp = NULL;
	if (cmd[i][0] == '+' || cmd[i][0] == '-')
	{
		if (ft_isdigit(cmd[i][1]))
			res = ft_atoi(cmd[i]);
	}
	else if (ft_isdigit(cmd[i][0])
		|| (cmd[i][0] == '-' && ft_isdigit(cmd[i][1])))
	{
		if (neg == 1)
		{
			temp = ft_strjoin("-", cmd[i]);
			res = ft_atoi(temp);
		}
		else
			res = ft_atoi(cmd[i]);
	}
	if (temp != NULL)
		free(temp);
	return (res);
}

static int	exit_conditions(t_minishell *mshell, char **cmd, int i, int res)
{
	int	neg;

	neg = 0;
	if (i >= 2 && (!ft_isdigit(cmd[i][0])
		|| (cmd[i][0] == '-' && !ft_isdigit(cmd[i][1]))))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		mshell->exit_code = 1;
		return (1);
	}
	if (cmd[i][0] == '+' || cmd[i][0] == '-')
	{
		if (cmd[i][0] == '-')
			neg = 1;
		res = exit_helper(cmd, i, res, neg);
	}
	else if (ft_isdigit(cmd[i][0]))
		res = exit_helper(cmd, i, res, neg);
	else
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		mshell->exit_code = 255;
		return (1);
	}
	return (res);
}

int	run_exit(t_minishell *mshell, char **cmd, int i, int res)
{
	int		exited_with;
	char	*temp;

	temp = NULL;
	if (cmd[1] != NULL)
	{
		while (cmd[++i] != NULL)
		{
			exited_with = exit_conditions(mshell, cmd, i, res);
			if (exited_with == 255 || exited_with == 1)
				return (1);
		}
		if (mshell->exit_code != 255)
			exit_and_free(mshell, exited_with);
	}
	else
	{
		printf("exit\n");
		exit_and_free(mshell, 0);
	}
	return (0);
}
