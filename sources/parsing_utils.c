/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:10:06 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:17:11 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*skip_redir(const char *cmd)
{
	while (*cmd == '<' || *cmd == '>')
		cmd++;
	return (cmd);
}

const char	*skip_quotes(const char *cmd)
{
	char	quote;

	quote = *cmd++;
	while (*cmd != quote && *cmd != '\0')
		cmd++;
	if (*cmd == quote)
		cmd++;
	return (cmd);
}

static int	count_arg_count(const char *cmd, int count)
{
	while (*cmd != '\0')
	{
		cmd = skip_spaces(cmd);
		if (*cmd == '\0')
			break ;
		if (*cmd == '\'' || *cmd == '"')
			cmd = skip_quotes(cmd);
		else if (*cmd == '<' || *cmd == '>')
			cmd = skip_redir(cmd);
		else
		{
			while (*cmd != ' ' && *cmd != '\0' && *cmd != '\'' && *cmd != '"')
			{
				if (*cmd == '\\' && (*(cmd + 1) == '\'' || *(cmd + 1) == '"'))
					cmd++;
				cmd++;
			}
		}
		count++;
	}
	return (count);
}

/*
- Similar to ft_split but splits given parameter with spaces and skips
	few special characters like " ' ", " " " and " \ ".
- Returns array of null terminated strings to run with execve.
*/
char	**get_cmd(const char *cmd)
{
	char		**args;
	char		*arg;
	int			i;
	const char	*next_cmd;
	int			arg_count;

	arg_count = count_arg_count(cmd, 0);
	args = malloc(arg_count * sizeof(char *) + 1);
	if (!args)
		return (NULL);
	i = 0;
	while (*cmd != '\0' && i < arg_count)
	{
		cmd = skip_spaces(cmd);
		if (*cmd == '\0')
			break ;
		next_cmd = copy_arg(cmd, &arg, 0, NULL);
		if (arg && *arg)
			args[i++] = arg;
		else
			free(arg);
		cmd = next_cmd;
	}
	args[i] = NULL;
	return (args);
}
