/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/13 22:39:32 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**split_by_cmds(char *input, int num_of_cmds, int l, int k)
{
	char	**arr;
	int		cmdlen;
	int		i;

	arr = malloc(sizeof(char *) * num_of_cmds + 1);
	if (!arr)
		return (NULL);
	while (input[l] && k < num_of_cmds)
	{
		i = 0;
		cmdlen = 0;
		while (input[l + cmdlen] && input[l + cmdlen] != '|')
			cmdlen++;
		arr[k] = malloc(sizeof(char) * (cmdlen + 1));
		if (!arr[k])
			return (NULL);
		while (i < cmdlen)
			arr[k][i++] = input[l++];
		arr[k][i] = '\0';
		k++;
		if (input[l] == '|')
			l++;
	}
	arr[k] = NULL;
	return (arr);
}

int	parse_command(t_minishell *mshell)
{
	char		**temp_commands;
	int			i;

	i = 0;
	temp_commands = split_by_cmds(mshell->input_cmd, mshell->num_of_cmds, 0, 0);
	if (!temp_commands)
		return (1);
	mshell->cmds = malloc(sizeof(t_commands *) * (mshell->num_of_cmds + 1));
	if (!mshell->cmds)
		return (1);
	while (mshell->num_of_cmds > i)
	{
		mshell->cmds[i] = malloc(sizeof(t_commands));
		if (!mshell->cmds[i])
			return (1);
		mshell->cmds[i]->cmd = get_cmd(temp_commands[i]);
		i++;
	}
	mshell->cmds[i] = NULL;
	i = 0;
	while (temp_commands[i])
		free(temp_commands[i++]);
	free(temp_commands);
	return (0);
}

/*
- Counts number of pipes and saves result to struct.
*/
void	count_pipes(t_minishell *mshell, char *input_cmd)
{
	int	i;

	i = 0;
	while (input_cmd[i])
	{
		if (input_cmd[i] == '|')
			mshell->num_of_pipes++;
		i++;
	}
	if (mshell->num_of_pipes > 0)
	{
		i--;
		while (input_cmd[i] == ' ')
			i--;
		if (input_cmd[i] == '|')
		{
			mshell->ends_with_pipe = true;
		}
	}
	mshell->num_of_cmds = mshell->num_of_pipes + 1;
}

void	valle(t_minishell *mshell)
{
	mshell->num_of_pipes = 0;
	if (mshell->input_cmd[0] == '\0')
		return ;
	if (parse_command(mshell) == 1)
	{
		free_commands(mshell);
	}
	if (check_cmd(mshell))
		return ;
	if (check_valid_redir(mshell))
		return ;
	// global_signal = 0;
	run_commands(mshell);
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
			l++;
		}
		free(mshell->cmds[i]->cmd);
		free(mshell->cmds[i]);
		i++;
	}
	free(mshell->cmds);
}

void	run_commands(t_minishell *mshell)
{
	int		i;
	int		pipefd[2];
	int		fd_in;
	int		status;

	i = 0;
	fd_in = 0;
	while (mshell->cmds[i])
	{
		// check_exit_code(mshell->cmds[i]->cmd);
		pipe(pipefd);
		if (fork() == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (mshell->cmds[i + 1])
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			execute_cmd(mshell, mshell->cmds[i]->cmd, mshell->env);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				global_signal = WEXITSTATUS(status);
			close(pipefd[1]);
			fd_in = pipefd[0];
			i++;
		}
	}
}

void	execute_cmd(t_minishell *mshell, char **cmd, t_env **env)
{
	char	*path;
	char	**env_arr;

	if (check_builtins(mshell, cmd))
		exit (global_signal);
	if (check_redirections(cmd))
		exit (global_signal);
	path = find_path(cmd[0], env, 0);
	if (!path)
	{
		if (access(cmd[0], X_OK) == 0)
			path = cmd[0];
		else
		{
			error_str(cmd[0], 1);
			global_signal = 127;
			exit (global_signal);
		}
	}
	global_signal = 0;
	env_arr = env_to_char_array(env);
	if (execve(path, cmd, env_arr) == -1)
		free_env_arr(env_arr, path, cmd);
	exit (global_signal);
}

void	free_env_arr(char **env_arr, char *path, char **cmd)
{
	// printf("errno: %d\n", errno);
	int	i;

	i = 0;
	// (void)path;
	// (void)cmd;
	while (env_arr[i])
		free(env_arr[i++]);
	free(env_arr);
	if (path != cmd[0])
		free(path);
	if (errno == EACCES)
		global_signal = 126;
	else
		global_signal = 1;
}

void	error_str(char *av, int n)
{
	if (n == 1)
	{
		ft_putstr_fd("minisHell: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (n == 2)
	{
		ft_putstr_fd("minisHell: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (n == 3)
	{
		ft_putstr_fd("minisHell: permission denied: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (n == 4)
	{
		ft_putstr_fd("minisHell: undefined variable: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\n", 2);
	}
}

char	*find_path(char *cmd, t_env **env, int i)
{
	char	**paths;
	char	*part_path;
	char	*path;

	paths = ft_split(get_env_value(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free (paths[i]);
	free(paths);
	return (NULL);
}

char	**env_to_char_array(t_env **env)
{
	char	**envp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		envp[i] = ft_strjoin(env[i]->key, "=");
		envp[i] = ft_strjoin(envp[i], env[i]->value);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(t_env **env, char *key)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i]->key, key, ft_strlen(key) + 1) == 0)
			return (env[i]->value);
		i++;
	}
	return (NULL);
}

int	check_exit_code(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "$?", 3) == 0)
		{
			free(cmd[i]);
			cmd[i] = malloc(sizeof(char) * 4);
			if (!cmd[i])
				return (1);
			cmd[i] = ft_itoa(global_signal);
			return (0);
		}
		i++;
	}
	return (0);
}
