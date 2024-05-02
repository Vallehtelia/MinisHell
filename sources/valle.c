/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:49 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/02 19:53:16 by vvaalant         ###   ########.fr       */
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
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (input_cmd[i])
	{
		if (input_cmd[i] == '\'')
			s_quote++;
		if (input_cmd[i] == '"')
			d_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
	{
		ft_putstr_fd("minisHell: Close quotes!\n", 2);
		return (1);
	}
	return (0);
}

void	handle_values(t_minishell *mshell)
{
	int		i;
	int		l;
	char	*temp;
	char	*value;

	i = 0;
	while (mshell->cmds[i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l])
		{
			if (mshell->cmds[i]->cmd[l][0] != '\'' && l > 0)
			{
				temp = ft_strchr(mshell->cmds[i]->cmd[l], '$');
				if (temp)
				{
					value = get_env_value(mshell->env, temp + 1);
					if (value)
					{
						free(mshell->cmds[i]->cmd[l]);
						mshell->cmds[i]->cmd[l] = ft_strdup(value);
					}
				}
			}
			l++;
		}
		i++;
	}
}

void	remove_quotes(t_minishell *mshell)
{
	int		i;
	int		l;
	char	*temp;

	i = 0;
	while (mshell->cmds[i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l])
		{
			if (mshell->cmds[i]->cmd[l][0] == '\''
				|| mshell->cmds[i]->cmd[l][0] == '"')
			{
				temp = ft_strtrim(mshell->cmds[i]->cmd[l], "\'");
				free(mshell->cmds[i]->cmd[l]);
				mshell->cmds[i]->cmd[l] = temp;
			}
			l++;
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
	handle_values(mshell);
	remove_quotes(mshell);
	if (check_cmd(mshell))
	{
		free_commands(mshell);
		return ;
	}
	if (check_valid_redir(mshell))
		return ;
	mshell->quote_check = 0;
	mshell->quote_check_past = 0;
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
				mshell->exit_code = WEXITSTATUS(status);
			close(pipefd[1]);
			fd_in = pipefd[0];
			i++;
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
			error_str(mshell, cmd, 3);
			mshell->exit_code = 126;
			return (1);
		}
	}
	else
	{
		error_str(mshell, cmd, 1);
		mshell->exit_code = 127;
		return (1);
	}
}

void	execute_cmd(t_minishell *mshell, char **cmd, t_env **env)
{
	char	*path;
	char	**env_arr;

	if (check_builtins(mshell, cmd))
		exit (mshell->exit_code);
	if (check_redirections(mshell, cmd))
		exit (mshell->exit_code);
	path = find_path(cmd[0], env, 0);
	if (!path)
	{
		if (check_access(mshell, cmd[0]))
			exit (mshell->exit_code);
		path = ft_strdup(cmd[0]);
	}
	mshell->exit_code = 0;
	env_arr = env_to_char_array(env);
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
	if (errno == EACCES)
		mshell->exit_code = 126;
	else
		mshell->exit_code = 1;
}

void	error_str(t_minishell *mshell, char *av, int n)
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
		mshell->exit_code = 126;
	}
	else if (n == 3)
	{
		ft_putstr_fd("minisHell: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": permission denied\n", 2);
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

int	check_exit_code(t_minishell *mshell, char **cmd)
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
			cmd[i] = ft_itoa(mshell->exit_code);
			return (0);
		}
		i++;
	}
	return (0);
}
