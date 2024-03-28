#include "../includes/minishell.h"

static void	free_env(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->env[i])
	{
		free(mshell->env[i]->key);
		free(mshell->env[i]->value);
		free(mshell->env[i]);
		i++;
	}
	free(mshell->env);
}

void	exit_and_free(t_minishell *mshell, int errno)
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
	if (mshell->env)
		free_env(mshell);
	if(errno > 0)
		ft_printf("ERROR %i\n",errno);
	exit(errno);
}
