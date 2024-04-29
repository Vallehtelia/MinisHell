/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:10:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/25 20:15:14 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_variable(t_minishell *mshell, char *var, bool space)
{
	if (var[0] == '$' && var[1] == '\0')
		var = "$";
	else if (ft_strncmp(var, "$?", 3) == 0 && ft_strlen(var) == 2)
		var = ft_itoa(mshell->exit_code); // MALLOCCI. Pitaa kattoa miten suojataan ja freeataan
	else if (var[0] == '$')
	{
		var++;
		if(check_if_env_exists(mshell->env, var) == false)
			var = NULL;
		else
			var = get_env_value(mshell->env, var);
	}
	if (var != NULL)
	{
		printf("%s", var);
		if (space)
			printf(" ");
	}
}

void echo_print(t_minishell *mshell, char **cmd, int i)
{
	if (cmd[i + 1] == NULL)
		print_variable(mshell, cmd[i], false);
	else
		print_variable(mshell, cmd[i], true);
}

static bool	check_echo_to_file(t_minishell *mshell, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (check_output_redirection(mshell, cmd, i))
			return (true);
		i++;
	}
	return (false);
}

static int	echo(t_minishell *mshell, char **cmd, int i)
{
	if (check_echo_to_file(mshell, cmd))
		return (1);
	if (!cmd[i])
		printf("\n");
	else if (ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		while (ft_strncmp(cmd[i], "-n", 3) == 0)
			i++;
		while (cmd[i] != NULL)
		{
			echo_print(mshell, cmd, i);
			i++;
		}
	}
	else
	{
		while (cmd[i] != NULL)
		{
			echo_print(mshell, cmd, i);
			i++;
		}
		printf("\n");
	}
	mshell->exit_code = 0;
	return (0);
}

static void	get_pwd(t_minishell *mshell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("minishell: pwd: error retrieving current directory\n");
		mshell->exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
		mshell->exit_code = 0;
	}
}

int	run_exit(t_minishell *mshell, char **cmd)
{
	if (cmd[1] != NULL)
	{
		ft_printf("minishell: exit: too many arguments\n");
		mshell->exit_code = 1;
		return (1);
	}
	else
	{
		ft_printf("exit\n");
		exit_and_free(mshell, 0);
	}
	return (0);
}

static void	handle_env_var(t_minishell *mshell)
{
	struct stat	statbuf;
	char		*value;

	value = get_env_value(mshell->env, mshell->cmds[0]->cmd[0] + 1);
	if (value != NULL)
	{
		free(mshell->cmds[0]->cmd[0]);
		mshell->cmds[0]->cmd[0] = ft_strdup(value);
		if (stat(mshell->cmds[0]->cmd[0], &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				error_str(mshell, mshell->cmds[0]->cmd[0], 2);
			else if (statbuf.st_mode & S_IXUSR)
				execute_cmd(mshell, mshell->cmds[0]->cmd, mshell->env);
			else
				error_str(mshell, mshell->cmds[0]->cmd[0], 3);
		}
		else
			error_str(mshell, mshell->cmds[0]->cmd[0], 1);
	}
	else
		error_str(mshell, mshell->cmds[0]->cmd[0], 4);
}

void print_env(t_minishell *mshell)
{
	int i;

	i = 0;
	while (mshell->env[i])
	{
		ft_printf("%s=%s\n", mshell->env[i]->key, mshell->env[i]->value);
		i++;
	}
}

void print_env_export(t_minishell *mshell)
{
	int i;

	i = 0;
	char abc = 'A';
	while(abc <= 'z')
	{
		while (mshell->env[i])
		{
			if (mshell->env[i]->key[0] == abc)
				printf("declare -x %s=\"%s\"\n", mshell->env[i]->key, mshell->env[i]->value);
			i++;
		}
		abc++;
		i = 0;
	}
}

void export_env(t_minishell *mshell, char **cmd)
{
	int		i;
	int 	keylen;
	char	*key;
	char	*value;
	char	*env_entry;
	char	*del_pos;

	i = 1;
	if(!cmd[i])
	{
		print_env_export(mshell);
		return ;
	}
	while(cmd[i])
	{
		env_entry = cmd[i];
		del_pos = ft_strchr(cmd[i], '=');
		if (!del_pos && cmd[i + 1][0] == '=')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i + 1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			mshell->exit_code = 1;
			return ;
		}
		if (del_pos)
		{
			keylen = del_pos - env_entry;
			key = ft_strndup(env_entry, keylen);
			value = ft_strdup(del_pos + 1);
			add_env(mshell, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

int	check_builtins(t_minishell *mshell, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		if (echo(mshell, cmd, 1))
			return (0);
		return (1);
	}
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		get_pwd(mshell);
		return (1);
	}
	if (check_exit_code(mshell, cmd))
	{
		return (1);
	}
	else if (cmd[0][0] == '$' && cmd[0][1] != '\0')
	{
		handle_env_var(mshell);
		return (1);
	}
	else if(ft_strncmp(cmd[0], "env", 4) == 0)
	{
		print_env(mshell);
		return (1);
	}
	return (0);
}
