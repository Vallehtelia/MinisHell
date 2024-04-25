#include "../includes/minishell.h"

void	free_env(t_minishell *mshell) // Otin staticin pois.. Katotaan haittaako?
{
	int	i;

	i = 0;
	if(mshell->env)
	{
		while (mshell->env[i])
		{
			free(mshell->env[i]->key);
			free(mshell->env[i]->value);
			free(mshell->env[i]);
			mshell->env[i] = NULL;
			i++;
		}
		free(mshell->env);
		mshell->env = NULL;
	}
}

void	exit_and_free(t_minishell *mshell, int errnum)
{
	free_workingdir(mshell);
	if (mshell->env)
		free_env(mshell);
	if (errnum > 0)
		ft_printf("ERROR %i\n", errnum);
	if (mshell->cmds)
		free_commands(mshell);
	exit(errnum);
}

void	free_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}
