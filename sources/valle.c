/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/24 18:29:20 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*skip_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int	cmd_lenght(char *input_cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (input_cmd[i] && input_cmd[i] != '|')
	{
		len++;
		i++;
	}
	i--;
	while (input_cmd[i] == ' ')
	{
		len--;
		i--;
	}
	return (len);
}

void	parse_command(t_minishell *mshell)
{
	t_commands	**cmd;
	int			i;
	int			y;
	// int			x;

	i = 0;
	cmd = mshell->cmd;
	cmd = malloc(sizeof(t_commands) * mshell->num_of_cmds);
	if (!cmd)
		return ;
	if (mshell->input_cmd)
	{
		skip_spaces(mshell->input_cmd);
		y = 0;
		printf("%i\n", cmd_lenght(mshell->input_cmd));
		// while (y < mshell->num_of_cmds)
		// {

		// }
	}
}

/*
- Counts number of pipes and saves result to struct.
*/
static void	count_pipes(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->input_cmd[i])
	{
		if (mshell->input_cmd[i] == '|')
			mshell->num_of_pipes++;
		i++;
	}
	mshell->num_of_cmds = mshell->num_of_pipes + 1;
}

void	valle(t_minishell *mshell)
{
	mshell->num_of_pipes = 0;
	count_pipes(mshell);
	parse_command(mshell);

}

void	valle_set(t_minishell *mshell)
{
	mshell->num_of_pipes = 0;
}
