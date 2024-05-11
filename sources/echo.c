/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:30:46 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:32:27 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_variable(char *var, bool space)
{
	if (var != NULL)
	{
		printf("%s", var);
		if (space)
			printf(" ");
	}
}

static void	echo_print(char **cmd, int i)
{
	char	*s_quote;
	char	*d_quote;

	s_quote = "'";
	d_quote = "\"";
	if ((ft_strncmp(cmd[i], d_quote, 2) == 0)
		|| (ft_strncmp(cmd[i], s_quote, 2) == 0))
	{
		print_variable(cmd[i], false);
	}
	else if ((cmd[i + 1] == NULL) || (ft_strncmp(cmd[i + 1], d_quote, 2) == 0)
		|| (ft_strncmp(cmd[i + 1], s_quote, 2) == 0))
		print_variable(cmd[i], false);
	else
		print_variable(cmd[i], true);
}

static bool	check_echo_to_file(t_minishell *mshell, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (check_output_redirection(mshell, cmd, i))
			return (true);
		i++;
	}
	return (false);
}

int	echo(t_minishell *mshell, char **cmd, int i)
{
	if (check_echo_to_file(mshell, cmd))
		return (1);
	if (!cmd[i])
		printf("\n");
	else if (ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		while (ft_strncmp(cmd[i], "-n", 3) == 0)
			i++;
		while (cmd[i] != NULL)
		{
			echo_print(cmd, i);
			i++;
		}
	}
	else
	{
		while (cmd[i] != NULL)
		{
			echo_print(cmd, i);
			i++;
		}
		printf("\n");
	}
	mshell->exit_code = 0;
	return (0);
}
