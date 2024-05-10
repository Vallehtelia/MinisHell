/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/08 18:02:38 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_cmdlen(char *input, int l)
{
	int		cmdlen;
	char	quote_type;

	cmdlen = 0;
	while (input[l + cmdlen] && input[l + cmdlen] != '|')
	{
		if (input[l + cmdlen] == '\'' || input[l + cmdlen] == '"')
		{
			quote_type = input[l + cmdlen];
			cmdlen++;
			while (input[l + cmdlen] && input[l + cmdlen] != quote_type)
				cmdlen++;
			if (input[l + cmdlen] == quote_type)
				cmdlen++;
		}
		else
			cmdlen++;
	}
	return (cmdlen);
}

static char	**split_by_cmds(char *input, int num_of_cmds, int l, int k)
{
	char	**arr;
	int		cmdlen;
	int		i;

	arr = malloc(sizeof(char *) * (num_of_cmds + 1));
	if (!arr)
		return (NULL);
	while (input[l] && k < num_of_cmds)
	{
		i = 0;
		cmdlen = count_cmdlen(input, l);
		arr[k] = malloc(sizeof(char) * (cmdlen + 1));
		if (!arr[k])
		{
			free_arr(arr, k);
			return (NULL);
		}
		while (i < cmdlen)
			arr[k][i++] = input[l++];
		arr[k++][i] = '\0';
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
void	count_pipes(t_minishell *mshell, char *input_cmd, int i, bool in_quote)
{
	while (input_cmd[i])
	{
		if (input_cmd[i] == '\'' || input_cmd[i] == '"')
		{
			if (in_quote == true)
				in_quote = false;
			else
				in_quote = true;
			i++;
		}
		if (input_cmd[i] == '|' && in_quote == false)
			mshell->num_of_pipes++;
		i++;
	}
	if (mshell->num_of_pipes > 0)
	{
		i--;
		while (input_cmd[i] == ' ')
			i--;
		if (input_cmd[i] == '|')
			mshell->ends_with_pipe = true;
	}
	mshell->num_of_cmds = mshell->num_of_pipes + 1;
}

int	count_quotes(char *input_cmd)
{
	int		i;
	char	quote_type;
	int		s_quote;

	i = -1;
	s_quote = 0;
	while (input_cmd[++i])
	{
		if (input_cmd[i] == '\'' || input_cmd[i] == '"')
		{
			quote_type = input_cmd[i];
			s_quote++;
			i++;
			while (input_cmd[i] && input_cmd[i] != quote_type)
				i++;
			if (input_cmd[i] == quote_type)
				s_quote++;
		}
	}
	if (s_quote % 2 != 0)
	{
		ft_putstr_fd("minisHell: Close quotes!\n", 2);
		return (1);
	}
	return (0);
}

int	builtin_check(t_minishell *mshell, int i)
{
	if (ft_strncmp(mshell->cmds[i]->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(mshell->cmds[i]->cmd[0], "exit", 5) == 0)
		return (1);
	return (0);
}

// int	change_value(t_minishell *mshell, int i, int l, int cmd_check)
// {
// 	int		k;
// 	int		j;
// 	char	*temp;
// 	char	*value;
// 	char	*temp_two;
// 	char	*temp_three;

// 	k = 0;
// 	value = NULL;
// 	while (mshell->cmds[i]->cmd[l][k])
// 	{
// 		if (mshell->cmds[i]->cmd[l][k] == '$'
// 			&& (mshell->cmds[i]->cmd[l][k + 1] != '\0'
// 			&& mshell->cmds[i]->cmd[l][k + 1] != ' ')
// 			&& mshell->cmds[i]->cmd[l][k + 1] != '"')
// 		{
// 			j = k;
// 			while (mshell->cmds[i]->cmd[l][j] && mshell->cmds[i]->cmd[l][j] != ' '
// 				&& mshell->cmds[i]->cmd[l][j] != '"')
// 				j++;
// 			temp = ft_strndup(mshell->cmds[i]->cmd[l] + k, j - k);
// 			value = get_env_value(mshell->env, temp + 1);
// 			free(temp);
// 			temp = ft_strndup(mshell->cmds[i]->cmd[l], k);
// 			if (value)
// 			{
// 				if (cmd_check == 0)
// 				{
// 					if (handle_env_var(mshell, value))
// 					{
// 						free(temp);
// 						return (1);
// 					}
// 				}
// 				temp_two = ft_strjoin(temp, value);
// 				temp_three = ft_strjoin(temp_two, mshell->cmds[i]->cmd[l] + j);
// 				free(mshell->cmds[i]->cmd[l]);
// 				mshell->cmds[i]->cmd[l] = temp_three;
// 				free(temp_two);
// 			}
// 			else
// 			{
// 				temp_two = ft_strndup(mshell->cmds[i]->cmd[l], k);
// 				temp_three = ft_strndup(mshell->cmds[i]->cmd[l] + j, ft_strlen(mshell->cmds[i]->cmd[l] - j));
// 				free(mshell->cmds[i]->cmd[l]);
// 				mshell->cmds[i]->cmd[l] = ft_strjoin(temp_two, temp_three);
// 				free(temp_two);
// 				free(temp_three);
// 			}
// 			k = j - 1;
// 			free(temp);
// 		}
// 		k++;
// 	}
// 	if (value == NULL && k == 0)
// 		return (1);
// 	return (0);
// }

int change_value(t_minishell *mshell, int i, int l, int cmd_check)
{
	int		k;
	int		j;
	char	*temp;
	char	*value;
	char	*temp_two;
	char	*temp_three;

	k = 0;
	value = NULL;
	while (mshell->cmds[i]->cmd[l][k])
	{
		if (mshell->cmds[i]->cmd[l][k] == '$'
			&& mshell->cmds[i]->cmd[l][k + 1] != '\0'
			&& mshell->cmds[i]->cmd[l][k + 1] != ' '
			&& mshell->cmds[i]->cmd[l][k + 1] != '"')
		{
			j = k + 1;
			while (mshell->cmds[i]->cmd[l][j]
				&& mshell->cmds[i]->cmd[l][j] != ' '
				&& mshell->cmds[i]->cmd[l][j] != '"')
				j++;
			temp = ft_strndup(mshell->cmds[i]->cmd[l] + k + 1, j - (k + 1));
			value = get_env_value(mshell->env, temp);
			free(temp);
			if (value)
			{
				if (cmd_check == 0)
				{
					if (handle_env_var(mshell, value))
						return (1);
				}
				temp = ft_strndup(mshell->cmds[i]->cmd[l], k);
				temp_two = ft_strjoin(temp, value);
				temp_three = ft_strjoin(temp_two, mshell->cmds[i]->cmd[l] + j);
				free(mshell->cmds[i]->cmd[l]);
				mshell->cmds[i]->cmd[l] = temp_three;
				free(temp);
				free(temp_two);
			}
			else
			{
				temp_two = ft_strndup(mshell->cmds[i]->cmd[l], k);
				temp_three = ft_strndup(mshell->cmds[i]->cmd[l] + j,
						strlen(mshell->cmds[i]->cmd[l]) - j);
				free(mshell->cmds[i]->cmd[l]);
				mshell->cmds[i]->cmd[l] = ft_strjoin(temp_two, temp_three);
				free(temp_two);
				free(temp_three);
			}
			k = j;
		}
		k++;
	}
	return (value == NULL && k == 0);
}


int	handle_values(t_minishell *mshell, int i)
{
	int		l;
	int		move_index;
	int		cmd_check;

	while (mshell->cmds[++i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l] != NULL)
		{
			cmd_check = builtin_check(mshell, i);
			if (mshell->cmds[i]->cmd[l][0] == '\'')
			{
				l++;
				continue ;
			}
			if (check_exit_code(mshell, i, l))
				return (1);
			if (change_value(mshell, i, l, cmd_check))
				return (1);
			if (mshell->cmds[i]->cmd[l] && ft_strlen(mshell->cmds[i]->cmd[l]) == 0)
			{
				free(mshell->cmds[i]->cmd[l]);
				move_index = l;
				while (mshell->cmds[i]->cmd[move_index + 1])
				{
					mshell->cmds[i]->cmd[move_index] = mshell->cmds[i]->cmd[move_index + 1];
					move_index++;
				}
				mshell->cmds[i]->cmd[move_index] = NULL;
				if (mshell->cmds[i]->cmd[l] == NULL)
					break ;
			}

			l++;
		}
	}
	if (mshell->cmds[0]->cmd[0] == NULL)
		return (1);
	return (0);
}

// void	remove_quotes(t_minishell *mshell)
// {
// 	int		i;
// 	int		l;
// 	char	*temp;

// 	i = 0;
// 	while (mshell->cmds[i])
// 	{
// 		l = 0;
// 		while (mshell->cmds[i]->cmd[l])
// 		{
// 			if (mshell->cmds[i]->cmd[l][0] == '\'')
// 			{
// 				temp = ft_strtrim(mshell->cmds[i]->cmd[l], "\'");
// 				free(mshell->cmds[i]->cmd[l]);
// 				mshell->cmds[i]->cmd[l] = temp;
// 			}
// 			else if (mshell->cmds[i]->cmd[l][0] == '"')
// 			{
// 				temp = ft_strtrim(mshell->cmds[i]->cmd[l], "\"");
// 				free(mshell->cmds[i]->cmd[l]);
// 				mshell->cmds[i]->cmd[l] = temp;
// 			}
// 			l++;
// 		}
// 		i++;
// 	}
// }

void	remove_quotes(char **cmd, int j)
{
	char	*result;
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	result = malloc(strlen(*cmd) + 1);
	while ((*cmd)[++i])
	{
		if (((*cmd)[i] == '\'' || (*cmd)[i] == '"') && (i == 0 || (*cmd)[i - 1] != '\\'))
		{
			if (quote == 0)
				quote = (*cmd)[i];
			else if (quote == (*cmd)[i])
				quote = 0;
			else
				result[j++] = (*cmd)[i];
		}
		else
			result[j++] = (*cmd)[i];
	}
	result[j] = '\0';
	free(*cmd);
	*cmd = result;
}

void remove_quotes_from_cmds(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->cmds[i])
	{
		int j = 0;
		while (mshell->cmds[i]->cmd[j])
		{
			remove_quotes(&mshell->cmds[i]->cmd[j], 0);
			j++;
		}
		i++;
	}
}

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
	if (handle_values(mshell, -1))
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
	// for (int i = 0; mshell->cmds[i]; i++)
	// {
	// 	for (int l = 0; mshell->cmds[i]->cmd[l]; l++)
	// 		printf("[%i][%i] %s\n", i, l, mshell->cmds[i]->cmd[l]);
	// }
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
			l++;
		}
		free(mshell->cmds[i]->cmd);
		free(mshell->cmds[i]);
		i++;
	}
	free(mshell->cmds);
}

// void	run_commands(t_minishell *mshell)
// {
// 	int		i;
// 	int		pipefd[2];
// 	int		fd_in;
// 	int		status;

// 	i = 0;
// 	fd_in = 0;
// 	while (mshell->cmds[i])
// 	{
// 		pipe(pipefd);
// 		if (fork() == 0)
// 		{
// 			if (fd_in != 0)
// 			{
// 				dup2(fd_in, 0);
// 				close(fd_in);
// 			}
// 			if (mshell->cmds[i + 1])
// 				dup2(pipefd[1], 1);
// 			close(pipefd[0]);
// 			execute_cmd(mshell, mshell->cmds[i]->cmd, mshell->env);
// 		}
// 		else
// 		{
// 			wait(&status);
// 			if (WIFEXITED(status))
// 				mshell->exit_code = WEXITSTATUS(status);
// 			close(pipefd[1]);
// 			fd_in = pipefd[0];
// 			i++;
// 		}
// 	}
// }

void	run_commands(t_minishell *mshell, int i, int fd_in)
{
	int	pipefd[2];
	int	status;
	int child_pid;

	if (mshell->cmds[i])
	{
		if (mshell->cmds[i + 1])
		{
			if (pipe(pipefd) == -1)
			{
				ft_putstr_fd("minisHell: pipe error\n", 2);
				mshell->exit_code = 1;
				return ;
			}
		}
		signal_execute();
		child_pid = fork();
		if (child_pid == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (mshell->cmds[i + 1])
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execute_cmd(mshell, mshell->cmds[i]->cmd, mshell->env , child_pid);
		}
		else
		{
			if (fd_in != 0)
				close(fd_in);
			if (mshell->cmds[i + 1])
			{
				close(pipefd[1]);
				run_commands(mshell, i + 1, pipefd[0]);
			}
			wait(&status);
			if (WIFEXITED(status))
				mshell->exit_code = WEXITSTATUS(status);
		}
	}
}

int	check_access(t_minishell *mshell, char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		else
		{
			error_str(mshell, cmd, ": Permission denied", 1);
			mshell->exit_code = 126;
			return (1);
		}
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

void	execute_cmd(t_minishell *mshell, char **cmd, t_env **env, int child_pid)
{
	char	*path;
	char	**env_arr;

	// for (int i = 0; mshell->cmds[i]; i++)
	// {
	// 	for (int l = 0; mshell->cmds[i]->cmd[l]; l++)
	// 		printf("[%i][%i] %s\n", i, l, mshell->cmds[i]->cmd[l]);
	// }
	if (check_redirections(mshell, cmd, child_pid))
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

void	free_env_arr(t_minishell *mshell, char **env_arr, char *path, char **cmd)
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

void	error_str(t_minishell *mshell, char *av, char *str, int n)
{
	char	*temp;

	if (ft_strncmp(av, "export", 6) == 0)
	{
		temp = ft_strjoin("`", str);
	}
	ft_putstr_fd("minisHell: ", 2);
	if (n == 1)
	{
		ft_putstr_fd(av, 2);
		ft_putendl_fd(str, 2); //": command not found\n"": permission denied\n"
	}
	else if (n == 2)
	{
		ft_putstr_fd(av, 2);
		ft_putendl_fd(str, 2); //": is a directory\n"
		mshell->exit_code = 126;
	}
	else if (n == 3)
	{
		ft_putstr_fd(av, 2);
		ft_putstr_fd(temp, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(temp);
	}
	else if (n == 4)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(av, 2);
		ft_putendl_fd(str, 2); //": No such file or directory\n"
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

int	check_exit_code(t_minishell *mshell, int i, int l)
{
	char	*temp;
	char	*temp_two;
	char	*new_cmd;
	char	*new_cmd_two;

	temp = NULL;
	temp = ft_strchr(mshell->cmds[i]->cmd[l], '$');
	if (temp)
	{
		if (ft_strncmp(temp, "$?", 2) == 0)
		{
			temp_two = ft_strndup(mshell->cmds[i]->cmd[l], temp - mshell->cmds[i]->cmd[l]);
			if (!temp_two)
				return (1);
			new_cmd_two = ft_itoa(mshell->exit_code);
			new_cmd = ft_strjoin(temp_two, new_cmd_two);
			free(new_cmd_two);
			if (!new_cmd)
			{
				free(temp_two);
				return (1);
			}
			if (temp + 2)
			{
				new_cmd_two = ft_strjoin(new_cmd, temp + 2);
				free(mshell->cmds[i]->cmd[l]);
				mshell->cmds[i]->cmd[l] = new_cmd_two;
				free(new_cmd);
			}
			else
			{
				free(mshell->cmds[i]->cmd[l]);
				mshell->cmds[i]->cmd[l] = new_cmd;
			}
			free(temp_two);
		}
	}
	return (0);
}
