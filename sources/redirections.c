/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:25:47 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/07 18:31:50 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	nullify_cmd(t_minishell *mshell, char **cmd, int i)
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
	mshell->exit_code = 0;
}

static void	handle_redir_input(t_minishell *mshell, char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_RDONLY);
	if (fd < 0)
	{
		error_str(mshell, cmd[i + 1], ": No such file or directory", 1);
		mshell->exit_code = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd[i]);
	free(cmd[i + 1]);
	nullify_cmd(mshell, cmd, i);
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

static void	handle_redir_input_heredoc(t_minishell *mshell, char **cmd, int i)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		mshell->exit_code = 1;
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
	nullify_cmd(mshell, cmd, i);
}

int	check_redirections(t_minishell *mshell, char **cmd)
{
	int	j;
	int	output;

	j = 0;
	output = 0;
	while (cmd[j])
	{
		if (ft_strncmp(cmd[j], "<", 2) == 0)
		{
			handle_redir_input(mshell, cmd, j);
			if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL)
				|| mshell->exit_code == 1)
				return (1);
			continue ;
		}
		else if (ft_strncmp(cmd[j], "<<", 3) == 0)
		{
			handle_redir_input_heredoc(mshell, cmd, j);
			if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL)
				|| mshell->exit_code == 1)
				return (1);
			continue ;
		}
		if (cmd[j] != NULL)
		{
			output = check_output_redirection(mshell, cmd, j);
			if (output == 1)
				return (1);
			else if (output == 2)
				continue ;
		}
		j++;
	}
	return (0);
}
