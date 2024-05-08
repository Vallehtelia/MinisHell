#include "../includes/minishell.h"

void matti(t_minishell *mshell)
{
	mshell->prompt_text = NULL;
	mshell->working_directory = NULL;
}

void set_working_directory(t_minishell *mshell)
{
	int i;

	i = 0;
	while(mshell->env[i])
	{
		if(ft_strncmp(mshell->env[i]->key, "PWD", 3) == 0)
		{
			free(mshell->env[i]->value);
			mshell->env[i]->value = NULL;
			mshell->env[i]->value = getcwd(NULL, 0);
			break;
		}
		i++;
	}
}

void set_old_pwd(t_minishell *mshell)
{
	char *temp;

	if(check_if_env_exists(mshell->env, "OLDPWD"))
	{
		set_env_value(mshell->env, "OLDPWD", get_env_value(mshell->env, "PWD"));
	}
	else
	{
		temp = get_env_value(mshell->env, "PWD");
		add_env(mshell, "OLDPWD", temp);
	}
}

void cd_have_path(t_minishell *mshell, char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
	{
		if (!S_ISDIR(statbuf.st_mode))
			error_str(mshell, path, ": Not a directory", 4);
		else if(access(path, X_OK) == -1)
			error_str(mshell, path, ": Permission denied", 4);
		else
		{
			set_old_pwd(mshell);
			if(chdir(path) == -1)
			{
				error_str(mshell, path, ": No such file or directory", 4);
				mshell->exit_code = 1;
			}
			else
			mshell->exit_code = 0;
		}
	}
}

void cd_no_path(t_minishell *mshell, char *path)
{
	path = getenv("HOME");
		set_old_pwd(mshell);
		if(!path)
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

void change_working_directory(t_minishell *mshell, char *path)
{
	if(path == NULL)
		cd_no_path(mshell, path);
	else if(path)
		cd_have_path(mshell, path);
	else
		mshell->exit_code = 0;
	set_working_directory(mshell);
}

void free_workingdir(t_minishell *mshell)
{
	if (mshell->prompt_text)
	{
		free(mshell->prompt_text);
		mshell->prompt_text = NULL;
	}
	if (mshell->working_directory)
	{
		free(mshell->working_directory);
		mshell->working_directory = NULL;
	}
}

void matti_set(t_minishell *mshell)
{
	char temp[1024];
	getcwd(temp, sizeof(temp));
	mshell->working_directory = malloc(ft_strlen(temp) + 1);
	if (!mshell->working_directory)
		exit_and_free(mshell, 1);
	ft_strlcpy(mshell->working_directory, temp, ft_strlen(temp) + 1);
		mshell->prompt_text = ft_strjoin(mshell->working_directory, " >>> ");
	if (!mshell->prompt_text)
		exit_and_free(mshell, 1);
}

