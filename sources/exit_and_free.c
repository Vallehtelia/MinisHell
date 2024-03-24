#include "../includes/minishell.h"

void exit_and_free(t_minishell *mshell, int errno)
{
	if(mshell->working_directory)
	{
		free(mshell->working_directory);
		mshell->working_directory = NULL;
	}
	if(mshell->input_cmd)
	{
		free(mshell->input_cmd);
		mshell->input_cmd = NULL;
	}
	if(errno > 0)
		ft_printf("ERROR %i\n",errno);
	exit(errno);
}
