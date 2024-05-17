/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:28:29 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/17 18:06:17 by vvaalant         ###   ########.fr       */
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

int	validate_exit(t_minishell *mshell, char **cmd, int i, int j)
{
	while (cmd[++i] != NULL)
	{
		j = -1;
		if (i >= 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			mshell->exit_code = 1;
			return (1);
		}
		while (cmd[i][++j] != '\0')
		{
			if (!ft_isdigit(cmd[i][j]) && cmd[i][j] != '+'
				&& cmd[i][j] != '-')
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				mshell->exit_code = 255;
				if (mshell->num_of_cmds == 1)
					exit_and_free(mshell, 255, 1);
				return (1);
			}
		}
	}
	return (0);
}

int	run_exit(t_minishell *mshell, char **cmd, int i, int res)
{
	int		exited_with;
	char	*temp;

	if (validate_exit(mshell, cmd, 0, 0))
		return (1);
	temp = NULL;
	if (cmd[1] != NULL)
	{
		while (cmd[++i] != NULL)
		{
			exited_with = exit_conditions(mshell, cmd, i, res);
			if ((exited_with == 255 || exited_with == 1)
				&& (ft_atoi(cmd[i]) != 1 && ft_atoi(cmd[i]) != 255))
				return (1);
		}
		if (mshell->exit_code != 255)
			exit_and_free(mshell, exited_with, 1);
	}
	else
	{
		printf("exit\n");
		exit_and_free(mshell, 0, 0);
	}
	return (0);
}
