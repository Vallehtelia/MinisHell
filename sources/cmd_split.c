/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:45:22 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/11 19:12:47 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static const char	*skip_spaces(const char *str)
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
static char	*copy_arg(const char *cmd, char **arg_out, int j, char *arg)
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

int	count_arg_count(const char *cmd, int count)
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
