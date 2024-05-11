/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:52:57 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 01:56:11 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_path(t_minishell *mshell, char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			if (ft_strncmp(cmd, "./", 2) == 0)
			{
				error_str(mshell, cmd, ": is a directory", 2);
				mshell->exit_code = 126;
			}
			else
			{
				error_str(mshell, cmd, ": command not found", 1);
				mshell->exit_code = 127;
			}
			return (1);
		}
	}
	return (0);
}

void	free_env_arr(t_minishell *mshell, char **env_arr, \
					char *path, char **cmd)
{
	int	i;

	i = 0;
	while (env_arr[i])
		free(env_arr[i++]);
	free(env_arr);
	if (path != cmd[0])
		free(path);
	if (errno == ENOENT)
	{
		error_str(mshell, cmd[0], ": command not found", 1);
		mshell->exit_code = 127;
	}
	else if (errno == EACCES)
	{
		error_str(mshell, cmd[0], ": Permission denied", 1);
		mshell->exit_code = 126;
	}
	else
		mshell->exit_code = 1;
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
