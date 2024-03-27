/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/28 01:26:39 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_lenght(char *input_cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (input_cmd[i] == ' ')
		i++;
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
	t_commands	*cmd;
	int			i;
	int			y;
	// int			x;

	i = 0;
	mshell->cmd = malloc(sizeof(t_commands) * mshell->num_of_cmds);
	if (!mshell->cmd)
		return ;
	if (mshell->input_cmd != NULL)
	{
		while (*mshell->input_cmd == ' ')
			mshell->input_cmd++;
		y = 0;
		cmd->cmd_lenght = cmd_lenght(mshell->input_cmd);
		//printf("%i\n", cmd->cmd_lenght);
		while (y < mshell->num_of_cmds)
		{

		}
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

void	free_commands(t_minishell *mshell)
{
	int	i;
	int	l;

	i = 0;
	while (mshell->cmd[i])
	{
		l = 0;
		while (mshell->cmd[i]->cmd[l])
		{
			free(mshell->cmd[i]->cmd[l]);
			l++;
		}
		i++;
	}
}
