/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:25:47 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/11 21:43:47 by vvaalant         ###   ########.fr       */
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

void	handle_redir_input(t_minishell *mshell, char **cmd, int i)
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

void	redir_input_heredoc(t_minishell *mshell, char **cmd, int i, char *l)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		mshell->exit_code = 1;
		return ;
	}
	while (1)
	{
		l = readline("> ");
		if (!l)
			break ;
		if (check_line(cmd, l, i))
			break ;
		ft_putendl_fd(l, pipefd[1]);
		free(l);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	free(cmd[i]);
	free(cmd[i + 1]);
	nullify_cmd(mshell, cmd, i);
}

int	check_redirections(t_minishell *mshell, char **cmd, int j, int output)
{
	int	input;

	while (cmd[j])
	{
		if (cmd[j] != NULL)
		{
			input = check_input_redirection(mshell, cmd, j);
			if (input == 1)
				return (1);
			else if (input == 2)
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
	//signal_basic(); // Lisatty heredoc singnaali kasittely
	return (0);
}
