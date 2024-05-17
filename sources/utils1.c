/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:09:11 by mrinkine          #+#    #+#             */
/*   Updated: 2024/05/17 18:07:27 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_working_directory(t_minishell *mshell)
{
	int	i;

	i = 0;
	while (mshell->env[i])
	{
		if (ft_strncmp(mshell->env[i]->key, "PWD", 3) == 0)
		{
			free(mshell->env[i]->value);
			mshell->env[i]->value = NULL;
			mshell->env[i]->value = getcwd(NULL, 0);
			break ;
		}
		i++;
	}
}

void	free_workingdir(t_minishell *mshell)
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

void	loop_set(t_minishell *mshell)
{
	char	temp[1024];

	signal_basic();
	mshell->prompt_text = NULL;
	mshell->working_directory = NULL;
	getcwd(temp, sizeof(temp));
	mshell->working_directory = malloc(ft_strlen(temp) + 1);
	if (!mshell->working_directory)
		exit_and_free(mshell, 1, 0);
	ft_strlcpy(mshell->working_directory, temp, ft_strlen(temp) + 1);
	mshell->prompt_text = ft_strjoin(mshell->working_directory, " >>> ");
	if (!mshell->prompt_text)
		exit_and_free(mshell, 1, 0);
}
