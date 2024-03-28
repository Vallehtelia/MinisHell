#include "../includes/minishell.h"

void matti(t_minishell *mshell)
{
	(void)mshell;
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
	(void)mshell;
	if (chdir(path) == -1)
	{
		printf("cd:  No such file or directory %s:\n", path);
	}
	// else
	// {
	// 	free_workingdir(mshell);
	// 	matti_set(mshell);
	// }
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
