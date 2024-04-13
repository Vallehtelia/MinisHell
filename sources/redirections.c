/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:25:47 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/13 23:32:51 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_redir_input(char **cmd, int i)
{
	int	fd;
	int	j;
	int temp;

	j = 0;
	fd = open(cmd[i + 1], O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", cmd[i + 1], strerror(errno));
		global_signal = 1;
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	free(cmd[i]);
	free(cmd[i + 1]);
	if (cmd[i + 2])
	{
		while (cmd[i + 2 + j])
		{
			cmd[i + j] = ft_strdup(cmd[i + 2 + j]);
			j++;
		}
		temp = i + 2;
		cmd[temp] = NULL;
		temp++;
		while (cmd[temp])
		{
			free(cmd[temp]);
			cmd[temp] = NULL;
			temp++;
		}
	}
}

// static void	handle_redir_input_heredoc(char **cmd, int i)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		printf("minishell: %s: %s\n", "heredoc", strerror(errno));
// 		global_signal = 1;
// 	}
// 	else
// 	{
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if (!line || ft_strncmp(line, cmd[i + 1], ft_strlen(cmd[i + 1])) == 0)
// 			{
// 				free(line);
// 				break ;
// 			}
// 			write(fd, line, ft_strlen(line));
// 			write(fd, "\n", 1);
// 			free(line);
// 		}
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	free(cmd[i]);
// 	free(cmd[i + 1]);
// 	cmd[i] = NULL;
// 	cmd[i + 1] = NULL;
// }

int	check_redirections(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (ft_strncmp(cmd[j], "<", 2) == 0)
		{
			handle_redir_input(cmd, j);
		}
		// else if (ft_strncmp(cmd[j], "<<", 3) == 0)
		// 	handle_redir_input_heredoc(cmd, i);
		// else if (ft_strncmp(cmd[j], ">", 2) == 0)
		// 	handle_redir_output(mshell, cmd, i);
		// else if (ft_strncmp(cmd[j], ">>", 3) == 0)
		// 	handle_redir_output_append(mshell, cmd, i);
		j++;
	}
	return (0);
}
