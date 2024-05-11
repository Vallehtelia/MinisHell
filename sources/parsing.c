/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:32 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:33:04 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(char **cmd, int j)
{
	char	*result;
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	result = malloc(strlen(*cmd) + 1);
	while ((*cmd)[++i])
	{
		if (((*cmd)[i] == '\'' || (*cmd)[i] == '"')
			&& (i == 0 || (*cmd)[i - 1] != '\\'))
		{
			if (quote == 0)
				quote = (*cmd)[i];
			else if (quote == (*cmd)[i])
				quote = 0;
			else
				result[j++] = (*cmd)[i];
		}
		else
			result[j++] = (*cmd)[i];
	}
	result[j] = '\0';
	free(*cmd);
	*cmd = result;
}

void	remove_quotes_from_cmds(t_minishell *mshell)
{
	int	i;
	int	j;

	i = 0;
	while (mshell->cmds[i])
	{
		j = 0;
		while (mshell->cmds[i]->cmd[j])
		{
			remove_quotes(&mshell->cmds[i]->cmd[j], 0);
			j++;
		}
		i++;
	}
}

void	handle_pipe_end(t_minishell *mshell, char *input)
{
	char	*temp;

	temp = NULL;
	while (temp == NULL)
	{
		temp = readline("> ");
		if (ft_cmdlen(temp) == 0)
		{
			free(temp);
			temp = NULL;
		}
	}
	temp = ft_strjoin(" ", temp);
	input = ft_strjoin(input, temp);
	free(temp);
	mshell->ends_with_pipe = false;
	mshell->input_cmd = input;
}

int	ft_cmdlen(char *str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while (*str == ' ')
			str++;
		while (*str)
		{
			str++;
			i++;
		}
	}
	return (i);
}
