#include "../includes/minishell.h"



void matti(t_minishell *mshell)
{
	(void)mshell;
	//   char cwd[100];
   	//	if (getcwd(cwd, sizeof(cwd)) != NULL)
    //   		printf("Current working dir: %s\n", cwd);

}
void matti_set(t_minishell *mshell)
{
	(void)mshell;
	char cwd[100];
   	if (getcwd(cwd, sizeof(cwd)) != NULL)
    	printf("Current working dir: %s\n", cwd);

}
