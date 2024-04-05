/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/04 19:42:53 by vvaalant         ###   ########.fr       */
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
static void	count_pipes(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->input_cmd[i])
	{
		if (mshell->input_cmd[i] == '|')
			mshell->num_of_pipes++;
		i++;
	}
	mshell->num_of_cmds = mshell->num_of_pipes + 1;
}

void	valle(t_minishell *mshell)
{
	mshell->num_of_pipes = 0;
	if (mshell->input_cmd[0] == '\0')
		return ;
	count_pipes(mshell);
	if (parse_command(mshell) == 1)
	{
		free_commands(mshell);
	}
	run_commands(mshell);
	// for (int i = 0; mshell->cmds[i]; i++)
	// {
	// 	for (int l = 0; mshell->cmds[i]->cmd[l]; l++)
	// 		printf("cmd %i--%i = %s\n", i + 1, l + 1, mshell->cmds[i]->cmd[l]);
	// 	printf("\n");
	// }
	// for (int i = 0; mshell->env[i]; i++)
	// {
	// 	printf("key: %s value: %s\n\n", mshell->env[i]->key, mshell->env[i]->value);
	// }
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
	//int		fd_out; // not used

	i = 0;
	fd_in = 0;
	//fd_out = 1;
	while (mshell->cmds[i])
	{
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
			execute_cmd(mshell->cmds[i]->cmd, mshell->env);
		}
		else
		{
			wait(NULL);
			close(pipefd[1]);
			fd_in = pipefd[0];
			i++;
		}
	}
}

void	execute_cmd(char **cmd, t_env **env)
{
	char	*path;
	char 	**env_arr;
	int		i;

	i = 0;
	path = find_path(cmd[0], env, 0);
	if (!path)
	{
		if (access(cmd[0], X_OK) == 0)
			path = cmd[0];
		else
		{
			while (cmd[i])
				free(cmd[i++]);
			free(cmd);
			error_str(cmd[0], 1);
			global_signal = 127;
			return ;
		}
	}
	env_arr = env_to_char_array(env);
	if (execve(path, cmd, env_arr) == -1)
		free_env_arr(env_arr, path, cmd);
}

void	free_env_arr(char **env_arr, char *path, char **cmd)
{
	int	i;

	i = 0;
	(void)path;
	(void)cmd;
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
	return (0);
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
