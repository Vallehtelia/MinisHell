/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:45:22 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:17:07 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*skip_spaces(const char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

const char	*copy_quoted(const char *cmd, char *arg, int *j, char quote)
{
	arg[(*j)++] = *cmd++;
	while (*cmd != quote && *cmd != '\0')
		arg[(*j)++] = *cmd++;
	if (*cmd == quote)
		arg[(*j)++] = *cmd++;
	if (*cmd == quote)
		cmd++;
	return (cmd);
}

const char	*copy_redirs(const char *cmd, char *arg, int *j)
{
	while (*cmd == '<' || *cmd == '>')
		arg[(*j)++] = *cmd++;
	return (cmd);
}

/*
- Does allocating for each argument and returns them to array.
*/
char	*copy_arg(const char *cmd, char **arg_out, int j, char *arg)
{
	arg = malloc(ft_strlen(cmd) + 1);
	if (!arg)
		return (NULL);
	while (*cmd != ' ' && *cmd != '\0')
	{
		if (*cmd == '<' || *cmd == '>')
		{
			cmd = copy_redirs(cmd, arg, &j);
			break ;
		}
		else if (*cmd == '\'' || *cmd == '"')
			cmd = copy_quoted(cmd, arg, &j, *cmd);
		else
		{
			while (*cmd != ' ' && *cmd != '\0' && *cmd != '\'' && *cmd != '"')
			{
				if (*cmd == '\\' && (*(cmd + 1) == '\'' || *(cmd + 1) == '"'))
					cmd++;
				arg[j++] = *cmd++;
			}
		}
	}
	arg[j] = '\0';
	*arg_out = arg;
	return ((char *)cmd);
}
