#include "../includes/minishell.h"

void matti(t_minishell *mshell)
{
	mshell->prompt_text = NULL;
	mshell->working_directory = NULL;
	//if (mshell->input_cmd[0] == 'c' && mshell->input_cmd[1] == 'd' && mshell->input_cmd[2] == ' ')
	//{
	//	change_working_directory(mshell, mshell->input_cmd + 3);
	//}
	//else
	//{
	//	printf("mshell: %s: command not found\n", mshell->input_cmd);
	//}
}
void change_working_directory(t_minishell *mshell, char *path)
{
	//(void)mshell;
	if(path == NULL)
	{
		path = getenv("HOME");
		if(!path)
		{
			printf("cd:  No such file or directory %s:\n", path);
			free_commands(mshell);
			mshell->exit_code  = 1;
			return ;
		}
		printf("path: %s\n", path);
		if (chdir(path) == -1)
		{
			printf("cd:  No such file or directory %s:\n", path);
			mshell->exit_code = 1;
		}
		else
			mshell->exit_code = 0;
		//free(path);
		//path = NULL;
	}
	else if (chdir(path) == -1)
	{
		printf("cd:  No such file or directory %s:\n", path);
		mshell->exit_code = 1;
	}
	else
		mshell->exit_code = 0;
	// else
	// {
	// 	free_workingdir(mshell);
	// 	matti_set(mshell);
	// }
	free_commands(mshell); //Lisäsin tän poistamaan leakit
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
	// getcwd(mshell->working_directory, sizeof(mshell->working_directory));
	// printf("Current working dir: %s\n", cwd);

	// mshell->input_cmd = malloc(ft_strlen(temp) + 1);

	mshell->prompt_text = ft_strjoin(mshell->working_directory, " >>> ");
	if (!mshell->prompt_text)
		exit_and_free(mshell, 1);
	// mshell->input_cmd = mshell->working_directory;
	// printf("\033[1;32mC:%s\\> \033[0m",mshell.working_directory);
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
