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

void change_working_directory(t_minishell *mshell, char *path)
{
	int i;

	//char *temp;
	if(path == NULL)
	{
		path = getenv("HOME");
		set_old_pwd(mshell);
		if(!path)
		{
			error_str(mshell, path, 4);
			free_commands(mshell);
			mshell->exit_code = 1;
			return ;
		}
		if (chdir(path) == -1)
		{
			error_str(mshell, path, 4);
			mshell->exit_code = 1;
		}
		else
			mshell->exit_code = 0;
	}
	else if(path)
	{
		set_old_pwd(mshell);
		i = chdir(path);
		if(i == -1)
		{
			error_str(mshell, path, 4);
			mshell->exit_code = 1;
		}

	}
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
//void print_prompt(t_minishell *mshell)
//{
//	printf("%s",mshell->prompt_text);
//}

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void handle_sigquit(int sig)
{
	(void)sig;
	write(1, "exit\n", 5);
}
void signal_handler(t_minishell *mshell)
{
	(void)mshell;
	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);

}
