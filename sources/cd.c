/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrinkine <mrinkine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:29 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/13 14:16:32 by mrinkine         ###   ########.fr       */
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

void	cd_no_path(t_minishell *mshell, char *path)
{
	if(check_if_env_exists(mshell->env, "HOME"))
	{
		//printf("path: %s\n", path);
		path = get_env_value(mshell->env, "HOME");
		//printf("path: %s\n", path);
	}
	else
	{
		printf("cd: HOME not set\n");
		return ;
	}
	set_old_pwd(mshell);
	if (!path)
	{
		error_str(mshell, path, ": No such file or directory", 4);
		free_commands(mshell);
		mshell->exit_code = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		error_str(mshell, path, ": No such file or directory", 4);
		mshell->exit_code = 1;
	}
	else
		mshell->exit_code = 0;
}

void	change_working_directory(t_minishell *mshell, char *path)
{
	if (path == NULL)
		cd_no_path(mshell, path);
	else if (path)
		cd_have_path(mshell, path);
	else
		mshell->exit_code = 0;
	set_working_directory(mshell);
}
