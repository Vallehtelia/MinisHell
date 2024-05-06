/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:45:22 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/03 22:15:48 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static const char	*skip_spaces(const char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/*
- Does allocating for each argument and returns them to array.
*/
// static char	*copy_arg(const char *cmd, char **arg_out, int j, char quote)
// {
// 	char		*arg;

// 	arg = malloc(ft_strlen(cmd) + 1);
// 	if (!arg)
// 		return (NULL);
// 	if (*cmd == '\'' || *cmd == '"')
// 	{
// 		quote = *cmd;
// 		if (quote == '"')
// 			cmd++;
// 		else
// 			arg[j++] = *cmd++;
// 		while (*cmd != quote && *cmd != '\0')
// 			arg[j++] = *cmd++;
// 		if (*cmd == quote && quote == '\'')
// 			arg[j++] = *cmd++;
// 		if (*cmd == quote)
// 			cmd++;
// 	}
// 	else
// 	{
// 		while (*cmd != ' ' && *cmd != '\0' && *cmd != '\'' && *cmd != '"')
// 		{
// 			if (*cmd == '\\' && (*(cmd + 1) == '\'' || *(cmd + 1) == '"'))
// 				cmd++;
// 			arg[j++] = *cmd++;
// 		}
// 	}
// 	arg[j] = '\0';
// 	*arg_out = arg;
// 	return ((char *)cmd);
// }

static char	*copy_arg(const char *cmd, char **arg_out, int j, char quote)
{
	char		*arg;

	arg = malloc(ft_strlen(cmd) + 1);
	if (!arg)
		return (NULL);
	if (*cmd == '\'' || *cmd == '"')
	{
		quote = *cmd;
		arg[j++] = *cmd++;
		while (*cmd != quote && *cmd != '\0')
			arg[j++] = *cmd++;
		if (*cmd == quote)
			arg[j++] = *cmd++;
		if (*cmd == quote)
			cmd++;
	}
	else
	{
		while (*cmd != ' ' && *cmd != '\0' && *cmd != '\'' && *cmd != '"')
		{
			if (*cmd == '\\' && (*(cmd + 1) == '\'' || *(cmd + 1) == '"'))
				cmd++;
			arg[j++] = *cmd++;
		}
	}
	arg[j] = '\0';
	*arg_out = arg;
	return ((char *)cmd);
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

	args = malloc(MAX_ARGS * sizeof(char *) + 1); // hankkiudu eroon max argsista
	if (!args)
		return (NULL);
	i = 0;
	while (*cmd != '\0' && i < MAX_ARGS - 1) // poista max_args
	{
		cmd = skip_spaces(cmd);
		if (*cmd == '\0')
			break ;
		next_cmd = copy_arg(cmd, &arg, 0, 0);
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
