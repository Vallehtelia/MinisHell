/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:06:27 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_cmdlen(char *input, int l)
{
	int		cmdlen;
	char	quote_type;

	cmdlen = 0;
	while (input[l + cmdlen] && input[l + cmdlen] != '|')
	{
		if (input[l + cmdlen] == '\'' || input[l + cmdlen] == '"')
		{
			quote_type = input[l + cmdlen];
			cmdlen++;
			while (input[l + cmdlen] && input[l + cmdlen] != quote_type)
				cmdlen++;
			if (input[l + cmdlen] == quote_type)
				cmdlen++;
		}
		else
			cmdlen++;
	}
	return (cmdlen);
}

static char	**split_by_cmds(char *input, int num_of_cmds, int l, int k)
{
	char	**arr;
	int		cmdlen;
	int		i;

	arr = malloc(sizeof(char *) * (num_of_cmds + 1));
	if (!arr)
		return (NULL);
	while (input[l] && k < num_of_cmds)
	{
		i = 0;
		cmdlen = count_cmdlen(input, l);
		arr[k] = malloc(sizeof(char) * (cmdlen + 1));
		if (!arr[k])
		{
			free_arr(arr, k);
			return (NULL);
		}
		while (i < cmdlen)
			arr[k][i++] = input[l++];
		arr[k++][i] = '\0';
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
	temp_commands = split_by_cmds(mshell->input_cmd, mshell->num_of_cmds, 0, 0);
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
void	count_pipes(t_minishell *mshell, char *input_cmd, int i, bool in_quote)
{
	while (input_cmd[i])
	{
		if (input_cmd[i] == '\'' || input_cmd[i] == '"')
		{
			if (in_quote == true)
				in_quote = false;
			else
				in_quote = true;
			i++;
		}
		if (input_cmd[i] == '|' && in_quote == false)
			mshell->num_of_pipes++;
		i++;
	}
	if (mshell->num_of_pipes > 0)
	{
		i--;
		while (input_cmd[i] == ' ')
			i--;
		if (input_cmd[i] == '|')
			mshell->ends_with_pipe = true;
	}
	mshell->num_of_cmds = mshell->num_of_pipes + 1;
}

int	count_quotes(char *input_cmd)
{
	int		i;
	char	quote_type;
	int		s_quote;

	i = -1;
	s_quote = 0;
	while (input_cmd[++i])
	{
		if (input_cmd[i] == '\'' || input_cmd[i] == '"')
		{
			quote_type = input_cmd[i];
			s_quote++;
			i++;
			while (input_cmd[i] && input_cmd[i] != quote_type)
				i++;
			if (input_cmd[i] == quote_type)
				s_quote++;
		}
	}
	if (s_quote % 2 != 0)
	{
		ft_putstr_fd("minisHell: Close quotes!\n", 2);
		return (1);
	}
	return (0);
}
