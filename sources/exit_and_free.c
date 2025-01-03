/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:38:54 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/17 18:05:33 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_minishell *mshell)
{
	int	i;

	i = 0;
	if (mshell->env)
	{
		while (mshell->env[i])
		{
			free(mshell->env[i]->key);
			free(mshell->env[i]->value);
			free(mshell->env[i]);
			mshell->env[i] = NULL;
			i++;
		}
		free(mshell->env);
		mshell->env = NULL;
	}
}

void	exit_and_free(t_minishell *mshell, int errnum, int print_exit)
{
	if (print_exit)
		ft_putendl_fd("exit", 1);
	free_workingdir(mshell);
	if (mshell->env)
		free_env(mshell);
	if (mshell->cmds)
		free_commands(mshell);
	exit(errnum);
}

void	free_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

void	error_str_helper(char *av, char *str, int n)
{
	char	*temp;

	temp = NULL;
	if (ft_strncmp(av, "export", 6) == 0)
		temp = ft_strjoin("`", str);
	if (n == 3)
	{
		ft_putstr_fd(av, 2);
		ft_putstr_fd(temp, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(temp);
		temp = NULL;
	}
	else if (n == 4)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(av, 2);
		ft_putendl_fd(str, 2);
	}
	if (temp)
		free(temp);
}

void	error_str(t_minishell *mshell, char *av, char *str, int n)
{
	ft_putstr_fd("minisHell: ", 2);
	if (n == 1)
	{
		ft_putstr_fd(av, 2);
		ft_putendl_fd(str, 2);
	}
	else if (n == 2)
	{
		ft_putstr_fd(av, 2);
		ft_putendl_fd(str, 2);
		mshell->exit_code = 126;
	}
	else if (n == 3 || n == 4)
		error_str_helper(av, str, n);
}
