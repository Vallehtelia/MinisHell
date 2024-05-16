/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:52:41 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 16:35:55 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	valle(t_minishell *mshell)
{
	mshell->num_of_pipes = 0;
	if (mshell->input_cmd[0] == '\0')
		return ;
	if (count_quotes(mshell->input_cmd))
		return ;
	if (parse_command(mshell) == 1 || mshell->cmds[0]->cmd[0] == NULL)
	{
		free_commands(mshell);
		return ;
	}
	if (handle_values(mshell, -1, 0, 0))
	{
		free_commands(mshell);
		return ;
	}
	remove_quotes_from_cmds(mshell);
	if (check_cmd(mshell))
	{
		free_commands(mshell);
		return ;
	}
	if (check_valid_redir(mshell))
		return ;
	run_commands(mshell, 0, 0);
	free_commands(mshell);
}

void	free_commands(t_minishell *mshell)
{
	int	i;
	int	l;

	i = 0;
	if (!mshell || !mshell->cmds)
		return ;
	while (mshell->cmds[i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l])
		{
			free(mshell->cmds[i]->cmd[l]);
			mshell->cmds[i]->cmd[l] = NULL;
			l++;
		}
		free(mshell->cmds[i]->cmd);
		free(mshell->cmds[i]);
		mshell->cmds[i] = NULL;
		i++;
	}
	free(mshell->cmds);
	mshell->cmds = NULL;
}

static int	check_access(t_minishell *mshell, char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		else if (open(cmd, O_RDONLY) == -1)
		{
			error_str(mshell, cmd, ": Permission denied", 1);
			mshell->exit_code = 126;
		}
		else
		{
			error_str(mshell, cmd, ": command not found", 1);
			mshell->exit_code = 127;
		}
		return (1);
	}
	else
	{
		if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
			error_str(mshell, cmd, ": No such file or directory", 1);
		else
			error_str(mshell, cmd, ": command not found", 1);
		mshell->exit_code = 127;
		return (1);
	}
}

void	execute_cmd(t_minishell *mshell, char **cmd, t_env **env)
{
	char	*path;
	char	**env_arr;

	if (check_redirections(mshell, cmd, 0, 0))
		exit (mshell->exit_code);
	if (check_builtins(mshell, cmd))
		exit (mshell->exit_code);
	path = find_path(cmd[0], env, 0);
	if (!path)
	{
		if (check_access(mshell, cmd[0]))
			exit (mshell->exit_code);
		path = ft_strdup(cmd[0]);
	}
	if (check_path(mshell, path))
		exit (mshell->exit_code);
	mshell->exit_code = 0;
	env_arr = env_to_char_array(env);
	signal_in_execve();
	if (execve(path, cmd, env_arr) == -1)
		free_env_arr(mshell, env_arr, path, cmd);
	exit (mshell->exit_code);
}
