/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:46:10 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/12 02:23:15 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_identifier(t_minishell *mshell, char *key, char *value, int equals)
{
	if (check_indentifier(key))
	{
		if (check_if_env_exists(mshell->env, key))
		{
			if (equals == 0)
				return (0);
			set_env_value(mshell->env, key, value, -1);
		}
		else
			add_env(mshell, key, value);
		free(key);
		free(value);
		return (0);
	}
	else
		return (1);
	return (0);
}

void	export_env_helper(t_minishell *mshell, char **cmd, int i)
{
	char	*key;
	char	*value;
	char	*del_pos;
	int		keylen;
	int		equals;

	keylen = ft_strlen(cmd[i]);
	del_pos = ft_strchr(cmd[i], '=');
	if (del_pos == NULL)
	{
		equals = 0;
		key = ft_substr(cmd[i], 0, keylen);
		value = ft_strdup("");
	}
	else
	{
		equals = 1;
		key = ft_substr(cmd[i], 0, del_pos - cmd[i]);
		value = ft_strdup(del_pos + 1);
	}
	if (handle_identifier(mshell, key, value, equals))
	{
		error_str(mshell, "export :", cmd[i], 3);
		mshell->exit_code = 1;
	}
}

void	export_env(t_minishell *mshell, char **cmd)
{
	int		i;

	i = 1;
	if (!cmd[i])
	{
		print_env_export(mshell);
		mshell->exit_code = 0;
		return ;
	}
	while (cmd[i])
	{
		export_env_helper(mshell, cmd, i);
		i++;
	}
}

int	confirm_env_chars(t_minishell *mshell, int i, int l, int k)
{
	if (mshell->cmds[i]->cmd[l][k] == '$'
		&& mshell->cmds[i]->cmd[l][k + 1] != '\0'
		&& mshell->cmds[i]->cmd[l][k + 1] != ' '
		&& mshell->cmds[i]->cmd[l][k + 1] != '"')
		return (1);
	return (0);
}

int	skip_env_chars(t_minishell *mshell, int i, int l, int j)
{
	while (mshell->cmds[i]->cmd[l][j] && mshell->cmds[i]->cmd[l][j] != ' '
		&& mshell->cmds[i]->cmd[l][j] != '"')
		j++;
	return (j);
}
