/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:40:11 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 01:47:26 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*change_value_novalue(char *cmd, int j, int k)
{
	char	*temp;
	char	*temp_two;
	char	*temp_three;

	temp = ft_strndup(cmd, k);
	temp_two = ft_strndup(cmd + j, strlen(cmd) - j);
	temp_three = ft_strjoin(temp, temp_two);
	free(temp);
	free(temp_two);
	return (temp_three);
}

static int	handle_cmd_check(t_minishell *mshell, char *value, int cmd_check)
{
	if (cmd_check == 0)
	{
		if (handle_env_var(mshell, value))
			return (1);
	}
	return (0);
}

static t_env_values	*allocate_env_values(int i, int l, int cmd_check)
{
	t_env_values	*env_value;

	env_value = malloc(sizeof(t_env_values));
	if (!env_value)
		return (NULL);
	env_value->i = i;
	env_value->l = l;
	env_value->cmd_chk = cmd_check;
	env_value->j = 0;
	env_value->k = 0;
	return (env_value);
}

int	change_value_helper(t_minishell *mshell, t_env_values *env, char *value)
{
	char	*temp;

	if (value)
	{
		if (handle_cmd_check(mshell, value, env->cmd_chk))
			return (1);
		temp = change_value_value(mshell->cmds[env->i]->cmd[env->l], \
			value, env->j, env->k);
		free(mshell->cmds[env->i]->cmd[env->l]);
		mshell->cmds[env->i]->cmd[env->l] = temp;
	}
	else
	{
		temp = change_value_novalue(mshell->cmds[env->i]->cmd[env->l], \
			env->j, env->k);
		free(mshell->cmds[env->i]->cmd[env->l]);
		mshell->cmds[env->i]->cmd[env->l] = temp;
	}
	return (0);
}

int	change_value(t_minishell *mshell, int i, int l, int cmd_check)
{
	char			*temp;
	char			*value;
	t_env_values	*env_value;

	env_value = allocate_env_values(i, l, cmd_check);
	while (mshell->cmds[i]->cmd[l][env_value->k])
	{
		if (confirm_env_chars(mshell, i, l, env_value->k))
		{
			env_value->j = env_value->k + 1;
			env_value->j = skip_env_chars(mshell, i, l, env_value->j);
			temp = ft_strndup(mshell->cmds[i]->cmd[l] + env_value->k + 1, \
				env_value->j - (env_value->k + 1));
			value = get_env_value(mshell->env, temp);
			free(temp);
			if (change_value_helper(mshell, env_value, value))
				return (1);
			env_value->k = env_value->j;
		}
		env_value->k++;
	}
	free(env_value);
	if (value == NULL && env_value->k == 0)
		return (1);
	return (0);
}
