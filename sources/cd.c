/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:29 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/15 14:03:57 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_have_path(t_minishell *mshell, char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
	{
		if (!S_ISDIR(statbuf.st_mode))
			error_str(mshell, path, ": Not a directory", 4);
		else if (access(path, X_OK) == -1)
			error_str(mshell, path, ": Permission denied", 4);
		else
		{
			set_old_pwd(mshell);
			if (chdir(path) == -1)
			{
				error_str(mshell, path, ": No such file or directory", 4);
				mshell->exit_code = 1;
			}
			else
				mshell->exit_code = 0;
		}
	}
}

int	cd_no_path(t_minishell *mshell)
{
	char	*path;

	path = NULL;
	if(check_if_env_exists(mshell->env, "HOME"))
		path = ft_strdup(get_env_value(mshell->env, "HOME"));
	else
	{
		printf("cd: HOME not set\n");
		mshell->exit_code = 1;
		return (1);
	}
	if (ft_strlen(path) < 1)
	{
		error_str(mshell, "HOME", " not set", 4);
		free_commands(mshell);
		mshell->exit_code = 1;
		return (1);
	}
	if (ft_strncmp(path, get_env_value(mshell->env, "PWD"), \
		ft_strlen(get_env_value(mshell->env, "PWD"))) == 0)
	{
		free(path);
		mshell->exit_code = 0;
		return (1);
	}
	int chdir_ret = chdir(path);
	if (chdir_ret == -1)
	{
		error_str(mshell, path, ": No such file or directory", 4);
		mshell->exit_code = 1;
	}
	else
		mshell->exit_code = 0;
	if (path)
		free(path);
	return (0);
}

void	change_working_directory(t_minishell *mshell, char *path)
{
	int	cnp_ret;

	cnp_ret = 0;
	if (path == NULL)
		cnp_ret = cd_no_path(mshell);
	else if (path)
		cd_have_path(mshell, path);
	else
		mshell->exit_code = 0;
	if (cnp_ret == 0)
	{
		set_working_directory(mshell);
	}
}
