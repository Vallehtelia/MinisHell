/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:25:08 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/11 21:43:53 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_output_redir(t_minishell *mshell, char **cmd, int j)
{
	int	fd;

	fd = open(cmd[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(cmd[j + 1], F_OK) == 0)
			error_str(mshell, cmd[j + 1], ": Permission denied", 1);
		else
			error_str(mshell, cmd[j + 1], ": No such file or directory", 1);
		mshell->exit_code = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(cmd[j]);
	free(cmd[j + 1]);
	nullify_cmd(mshell, cmd, j);
}

static void	handle_output_redir_append(t_minishell *mshell, char **cmd, int j)
{
	int	fd;

	fd = open(cmd[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		if (access(cmd[j + 1], F_OK) == 0)
			error_str(mshell, cmd[j + 1], ": Permission denied", 1);
		mshell->exit_code = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(cmd[j]);
	free(cmd[j + 1]);
	nullify_cmd(mshell, cmd, j);
}

int	check_output_redirection(t_minishell *mshell, char **cmd, int j)
{
	if (ft_strncmp(cmd[j], ">", 2) == 0)
	{
		handle_output_redir(mshell, cmd, j);
		if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL)
			|| mshell->exit_code == 1)
			return (1);
		else
			return (2);
	}
	else if (ft_strncmp(cmd[j], ">>", 3) == 0)
	{
		handle_output_redir_append(mshell, cmd, j);
		if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL)
			|| mshell->exit_code == 1)
			return (1);
		else
			return (2);
	}
	return (0);
}

int	check_input_redirection(t_minishell *mshell, char **cmd, int j)
{
	if (ft_strncmp(cmd[j], "<", 2) == 0)
	{
		handle_redir_input(mshell, cmd, j);
		if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL)
			|| mshell->exit_code == 1)
			return (1);
		else
			return (2);
	}
	else if (ft_strncmp(cmd[j], "<<", 3) == 0)
	{
		signal_heredoc();
		redir_input_heredoc(mshell, cmd, j, NULL);
		if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL)
			|| mshell->exit_code == 1)
			return (1);
		else
			return (2);
	}
	return (0);
}
