#include "../includes/minishell.h"



void matti(t_minishell *mshell)
{
	(void)mshell;
	//matti_set(mshell);
	//   char cwd[100];
   	//	if (getcwd(cwd, sizeof(cwd)) != NULL)
    //   		printf("Current working dir: %s\n", cwd);

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

}

