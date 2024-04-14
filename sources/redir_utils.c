/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:25:08 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/14 20:47:53 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_output_redir(char **cmd, int j)
{
	int	fd;

	fd = open(cmd[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", cmd[j + 1], strerror(errno));
		global_signal = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(cmd[j]);
	free(cmd[j + 1]);
	nullify_cmd(cmd, j);
}

static void	handle_output_redir_append(char **cmd, int j)
{
	int	fd;

	fd = open(cmd[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", cmd[j + 1], strerror(errno));
		global_signal = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(cmd[j]);
	free(cmd[j + 1]);
	nullify_cmd(cmd, j);
}

int	check_output_redirection(char **cmd, int j)
{
	if (ft_strncmp(cmd[j], ">", 2) == 0)
	{
		handle_output_redir(cmd, j);
		if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL))
			return (1);
	}
	else if (ft_strncmp(cmd[j], ">>", 3) == 0)
	{
		handle_output_redir_append(cmd, j);
		if ((cmd[j] == NULL && cmd[j - 1] == NULL) || (cmd[0] == NULL))
			return (1);
	}
	return (0);
}
