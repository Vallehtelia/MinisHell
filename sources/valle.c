/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/28 04:24:30 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	cmd_lenght(char *input_cmd)
// {
// 	int	len;
// 	int	i;

// 	len = 0;
// 	i = 0;
// 	while (input_cmd[i] == ' ' || input_cmd[i] == '|')
// 		i++;
// 	while (input_cmd[i] && input_cmd[i] != '|')
// 	{
// 		len++;
// 		i++;
// 	}
// 	i--;
// 	while (input_cmd[i] == ' ')
// 	{
// 		len--;
// 		i--;
// 	}
// 	return (len);
// }

static char	**split_by_cmds(char *input, int num_of_cmds)
{
	char	**arr;
	int		cmdlen;
	int		i;
	int		l;
	int		k;

	arr = malloc(sizeof(char *) * num_of_cmds + 1);
	if (!arr)
		return (NULL);
	l = 0;
	k = 0;
	while (input[l] && k < num_of_cmds)
	{
		i = 0;
		cmdlen = 0;
		while (input[l + cmdlen] && input[l + cmdlen] != '|')
			cmdlen++;
		arr[k] = malloc(sizeof(char) * (cmdlen + 1));
		if (!arr[k])
			return (NULL);
		while (i < cmdlen)
			arr[k][i++] = input[l++];
		arr[k][i] = '\0';
		k++;
		if (input[l] == '|')
			l++;
	}
	arr[k] = NULL;
	return (arr);
}

int	parse_command(t_minishell *mshell)
{
	char		**temp_commands;
	int			i;

	i = 0;
	temp_commands = split_by_cmds(mshell->input_cmd, mshell->num_of_cmds);
	if (!temp_commands)
		return (1);
	mshell->cmds = malloc(sizeof(t_commands *) * (mshell->num_of_cmds + 1));
	if (!mshell->cmds)
		return (1);
	while (mshell->num_of_cmds > i)
	{
		mshell->cmds[i] = malloc(sizeof(t_commands));
		if (!mshell->cmds[i])
			return (1);
		mshell->cmds[i]->cmd = get_cmd(temp_commands[i]);
		i++;
	}
	mshell->cmds[i] = NULL;
	i = 0;
	while (temp_commands[i])
		free(temp_commands[i++]);
	free(temp_commands);
	return (0);
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
	if (parse_command(mshell) == 1)
	{
		free_commands(mshell);
	}
	for (int i = 0; mshell->cmds[i]; i++)
	{
		for (int l = 0; mshell->cmds[i]->cmd[l]; l++)
			printf("cmd %i--%i = %s\n", i + 1, l + 1, mshell->cmds[i]->cmd[l]);
		printf("\n");
	}
	free_commands(mshell);
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
	if (!mshell || !mshell->cmds)
		return ;
	while (mshell->cmds[i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l])
		{
			free(mshell->cmds[i]->cmd[l]);
			l++;
		}
		free(mshell->cmds[i]->cmd);
		free(mshell->cmds[i]);
		i++;
	}
	free(mshell->cmds);
}
