#include "../includes/minishell.h"



void matti(t_minishell *mshell)
{
	(void)mshell;




}

void free_workingdir(t_minishell *mshell)
{
	//(void)mshell;
	if(mshell->input_cmd)
	{
		free(mshell->input_cmd);
		mshell->input_cmd = NULL;
	}



}
void matti_set(t_minishell *mshell)
{

	//(void)mshell;
	char temp[1024];
   	getcwd(temp, sizeof(temp));
	mshell->working_directory = malloc(ft_strlen(temp) + 1);
	// Tee mallokki checcki
	ft_strlcpy(mshell->working_directory,temp,ft_strlen(temp) + 1);
	//getcwd(mshell->working_directory, sizeof(mshell->working_directory));
    	//printf("Current working dir: %s\n", cwd);

	//mshell->input_cmd = malloc(ft_strlen(temp) + 1);

	mshell->input_cmd = ft_strjoin(mshell->working_directory, " >>> ");
	//mshell->input_cmd = mshell->working_directory;
	//printf("\033[1;32mC:%s\\> \033[0m",mshell.working_directory);

}

