/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:10:14 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/03 20:20:40 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_variable(char *var, bool space)
{
	if (var != NULL)
	{
		printf("%s", var);
		if (space)
			printf(" ");
	}
}

void echo_print(t_minishell *mshell, char **cmd, int i)
{
	(void)mshell;
	char	s_quote[2];
	char	d_quote[2];

	s_quote[0] = '\'';
	s_quote[1] = '\0';
	d_quote[0] = '"';
	d_quote[1] = '\0';
	if ((ft_strncmp(cmd[i], d_quote, 2) == 0) || (ft_strncmp(cmd[i], s_quote, 2) == 0))
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

int	run_exit(t_minishell *mshell, char **cmd, int i, int res)
{
	int		neg;
	char	*temp;

	neg = 0;
	temp = NULL;
	if (cmd[1] != NULL)
	{
		while (cmd[++i] != NULL)
		{
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
		}
		if (mshell->exit_code != 255)
			exit_and_free(mshell, res);
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
			error_str(mshell, env, 2);
		else if (statbuf.st_mode & S_IXUSR)
			return (0);
		else
			error_str(mshell, env, 3);
		return (1);
	}
	else
	{
		error_str(mshell, env, 1);
		return (1);
	}
	return (0);
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
	char	*cleaned_value;

	i = 1;
	if(!cmd[i])
	{
		print_env_export(mshell);
		mshell->exit_code = 0;
		return ;
	}
	while(cmd[i])
	{
		env_entry = cmd[i];
		del_pos = ft_strchr(cmd[i], '=');
		if (!del_pos && !cmd[i + 1])
		{
			mshell->exit_code = 1;
			return ;
		}
		if (!del_pos && cmd[i + 1][0] == '=')
		{
			cleaned_value = clean_value(cmd[i + 1]);
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cleaned_value, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			free(cleaned_value);
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
	// if (check_exit_code(mshell, cmd))
	// 	return (1);
	// else if (cmd[0][0] == '$' && cmd[0][1] != '\0')
	// {
	// 	if (handle_env_var(mshell))
	// 		return (1);
	// }
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
	return (0);
}
