/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:10:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/11 21:22:30 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_variable(char *var, bool space)
{
	if (var != NULL)
	{
		printf("%s", var);
		if (space)
			printf(" ");
	}
}

void	echo_print(char **cmd, int i)
{
	char	*s_quote;
	char	*d_quote;

	s_quote = "'";
	d_quote = "\"";
	if ((ft_strncmp(cmd[i], d_quote, 2) == 0)
		|| (ft_strncmp(cmd[i], s_quote, 2) == 0))
	{
		print_variable(cmd[i], false);
	}
	else if ((cmd[i + 1] == NULL) || (ft_strncmp(cmd[i + 1], d_quote, 2) == 0)
		|| (ft_strncmp(cmd[i + 1], s_quote, 2) == 0))
		print_variable(cmd[i], false);
	else
		print_variable(cmd[i], true);
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
			echo_print(cmd, i);
			i++;
		}
	}
	else
	{
		while (cmd[i] != NULL)
		{
			echo_print(cmd, i);
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

int	exit_helper(char **cmd, int i, int res, int neg)
{
	char	*temp;

	temp = NULL;
	if (cmd[i][0] == '+' || cmd[i][0] == '-')
	{
		if (ft_isdigit(cmd[i][1]))
			res = ft_atoi(cmd[i]);
	}
	else if (ft_isdigit(cmd[i][0])
		|| (cmd[i][0] == '-' && ft_isdigit(cmd[i][1])))
	{
		if (neg == 1)
		{
			temp = ft_strjoin("-", cmd[i]);
			res = ft_atoi(temp);
		}
		else
			res = ft_atoi(cmd[i]);
	}
	if (temp != NULL)
		free(temp);
	return (res);
}

int	exit_conditions(t_minishell *mshell, char **cmd, int i, int res)
{
	int	neg;

	neg = 0;
	if (i >= 2 && (!ft_isdigit(cmd[i][0])
		|| (cmd[i][0] == '-' && !ft_isdigit(cmd[i][1]))))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		mshell->exit_code = 1;
		return (1);
	}
	if (cmd[i][0] == '+' || cmd[i][0] == '-')
	{
		if (cmd[i][0] == '-')
			neg = 1;
		res = exit_helper(cmd, i, res, neg);
	}
	else if (ft_isdigit(cmd[i][0]))
		res = exit_helper(cmd, i, res, neg);
	else
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		mshell->exit_code = 255;
		return (1);
	}
	return (res);
}

int	run_exit(t_minishell *mshell, char **cmd, int i, int res)
{
	int		exited_with;
	char	*temp;

	temp = NULL;
	if (cmd[1] != NULL)
	{
		while (cmd[++i] != NULL)
		{
			exited_with = exit_conditions(mshell, cmd, i, res);
			if (exited_with == 255 || exited_with == 1)
				return (1);
		}
		if (mshell->exit_code != 255)
			exit_and_free(mshell, exited_with);
	}
	else
	{
		printf("exit\n");
		exit_and_free(mshell, 0);
	}
	return (0);
}

int	handle_env_var(t_minishell *mshell, char *env)
{
	struct stat	statbuf;

	if (stat(env, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			error_str(mshell, env, ": is a directory", 2);
		else if (statbuf.st_mode & S_IXUSR)
			return (0);
		else
			error_str(mshell, env, ": permission denied", 1);
		return (1);
	}
	else
	{
		error_str(mshell, env, ": command not found", 1);
		return (1);
	}
	return (0);
}

void	print_env(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->env[i])
	{
		if (mshell->env[i]->have_value)
		{
			printf("%s=%s\n", mshell->env[i]->key, mshell->env[i]->value);
		}
		i++;
	}
}

void	print_env_export(t_minishell *mshell)
{
	int		i;
	char	abc;

	i = 0;
	abc = 'A';
	while (abc <= 'z')
	{
		while (mshell->env[i])
		{
			if (mshell->env[i]->key[0] == abc)
			{
				if (mshell->env[i]->have_value)
					printf("declare -x %s=\"%s\"\n", \
					mshell->env[i]->key, mshell->env[i]->value);
				else
					printf("declare -x %s\n", mshell->env[i]->key);
			}
			i++;
		}
		abc++;
		i = 0;
	}
}

bool	check_indentifier(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (false);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	handle_identifier(t_minishell *mshell, char *key, char *value, int equals)
{
	if (check_indentifier(key))
	{
		if (check_if_env_exists(mshell->env, key))
		{
			if (equals == 0)
				return (0);
			set_env_value(mshell->env, key, value, -1);
		}
		else
			add_env(mshell, key, value);
		free(key);
		free(value);
		return (0);
	}
	else
		return (1);
	return (0);
}

void	export_env_helper(t_minishell *mshell, char **cmd, int i)
{
	char	*key;
	char	*value;
	char	*del_pos;
	int		keylen;
	int		equals;

	keylen = ft_strlen(cmd[i]);
	del_pos = ft_strchr(cmd[i], '=');
	if (del_pos == NULL)
	{
		equals = 0;
		key = ft_substr(cmd[i], 0, keylen);
		value = ft_strdup("");
	}
	else
	{
		equals = 1;
		key = ft_substr(cmd[i], 0, del_pos - cmd[i]);
		value = ft_strdup(del_pos + 1);
	}
	if (handle_identifier(mshell, key, value, equals))
	{
		error_str(mshell, "export :", cmd[i], 3);
		mshell->exit_code = 1;
	}
}

void	export_env(t_minishell *mshell, char **cmd)
{
	int		i;

	i = 1;
	if (!cmd[i])
	{
		print_env_export(mshell);
		mshell->exit_code = 0;
		return ;
	}
	while (cmd[i])
	{
		export_env_helper(mshell, cmd, i);
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
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
	{
		print_env(mshell);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
	{
		if (cmd[1] == NULL)
			print_env_export(mshell);
		return (1);
	}
	return (0);
}
