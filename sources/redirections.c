/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:25:47 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/14 20:16:01 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	nullify_cmd(char **cmd, int i)
{
	int	j;

	j = i;
	while (cmd[j + 2])
	{
		cmd[j] = cmd[j + 2];
		cmd[j + 2] = NULL;
		j++;
	}
	cmd[j] = NULL;
	global_signal = 0;
}

static void	handle_redir_input(char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", cmd[i + 1], strerror(errno));
		global_signal = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd[i]);
	free(cmd[i + 1]);
	nullify_cmd(cmd, i);
}

static int	check_line(char **cmd, char *line, int i)
{
	if ((ft_strncmp(line, cmd[i + 1], ft_strlen(cmd[i + 1])) == 0)
		&& (ft_strlen(line) == ft_strlen(cmd[i + 1])))
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	handle_redir_input_heredoc(char **cmd, int i)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		global_signal = 1;
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (check_line(cmd, line, i))
			break ;
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	free(cmd[i]);
	free(cmd[i + 1]);
	nullify_cmd(cmd, i);
}

int	check_redirections(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (ft_strncmp(cmd[j], "<", 2) == 0)
		{
			handle_redir_input(cmd, j);
			if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL))
				return (1);
		}
		else if (ft_strncmp(cmd[j], "<<", 3) == 0)
		{
			handle_redir_input_heredoc(cmd, j);
			if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL))
				return (1);
		}
		// else if (ft_strncmp(cmd[j], ">", 2) == 0)
		// 	handle_redir_output(mshell, cmd, i);
		// else if (ft_strncmp(cmd[j], ">>", 3) == 0)
		// 	handle_redir_output_append(mshell, cmd, i);
		j++;
	}
	return (0);
}
