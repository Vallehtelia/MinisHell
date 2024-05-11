/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:50:13 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/11 21:00:56 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	syntax_error_check(t_minishell *mshell, int i, int x)
{
	if (mshell->cmds[i]->cmd[x + 1] == NULL && mshell->cmds[i + 1] != NULL)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (mshell->cmds[i]->cmd[x + 1] == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_valid_redir(t_minishell *mshell)
{
	int	i;
	int	x;

	i = -1;
	while (mshell->cmds[++i])
	{
		x = 0;
		while (mshell->cmds[i]->cmd[x])
		{
			if ((ft_strncmp(mshell->cmds[i]->cmd[x], "<", 2) == 0)
				|| (ft_strncmp(mshell->cmds[i]->cmd[x], "<<", 3) == 0)
				|| (ft_strncmp(mshell->cmds[i]->cmd[x], ">", 2) == 0)
				|| (ft_strncmp(mshell->cmds[i]->cmd[x], ">>", 3) == 0))
			{
				if (syntax_error_check(mshell, i, x) == 1)
				{
					mshell->exit_code = 258;
					free_commands(mshell);
					return (1);
				}
			}
			x++;
		}
	}
	return (0);
}

static void	handle_redir_error(t_minishell *mshell, char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if (ft_strlen(cmd) > 2 && ft_strncmp(mshell->cmds[0]->cmd[0], "<", 1) == 0)
	{
		if (i == 3)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else if (i == 4)
			printf("minishell: syntax error near unexpected token `<'\n");
		else if (i == 5)
			printf("minishell: syntax error near unexpected token `<<'\n");
		else
			printf("minishell: syntax error near unexpected token `<<<'\n");
	}
	else if (ft_strlen(cmd) > 2
		&& ft_strncmp(mshell->cmds[0]->cmd[0], ">", 1) == 0)
	{
		if (i == 3)
			printf("minishell: syntax error near unexpected token `>'\n");
		else
			printf("minishell: syntax error near unexpected token `>>'\n");
	}
	mshell->exit_code = 258;
}

int	handle_export(t_minishell *mshell)
{
	int	i;
	int	l;

	i = 0;
	while (mshell->cmds[i])
	{
		l = 0;
		while (mshell->cmds[i]->cmd[l])
		{
			if (ft_strncmp(mshell->cmds[i]->cmd[l], "export", 7) == 0)
			{
				if (mshell->num_of_cmds == 1)
				{
					export_env(mshell, mshell->cmds[i]->cmd);
					return (1);
				}
				else
					return (0);
			}
			l++;
		}
		i++;
	}
	return (0);
}

int	confirm_redir_chars(char *str)
{
	if ((ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
		&& ft_strlen(str) > 2)
		return (1);
	else
		return (0);
}

int	check_cmd(t_minishell *mshell)
{
	if ((ft_strncmp(mshell->cmds[0]->cmd[0], "cd", 3) == 0))
	{
		change_working_directory(mshell, mshell->cmds[0]->cmd[1]);
		return (1);
	}
	if (handle_export(mshell))
		return (1);
	else if (ft_strncmp(mshell->cmds[0]->cmd[0], "unset", 6) == 0)
	{
		if (mshell->cmds[0]->cmd[1] != NULL)
			delete_env(mshell, mshell->cmds[0]->cmd[1]);
		return (1);
	}
	else if (ft_strncmp(mshell->cmds[0]->cmd[0], "exit", 5) == 0)
	{
		if (run_exit(mshell, mshell->cmds[0]->cmd, 0, 0))
			return (1);
	}
	else if (confirm_redir_chars(mshell->cmds[0]->cmd[0]))
	{
		handle_redir_error(mshell, mshell->cmds[0]->cmd[0]);
		return (1);
	}
	return (0);
}

void	print_shrek(void)
{
	printf("\033[2J\033[H");
	printf(GR"/* ******************************************************* */\n");
	printf("/*⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                           */\n");
	printf("/*⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀                           */\n");
	printf("/*⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀         :::      :::::::: */\n");
	printf("/*⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀       :+:      :+:    :+: */\n");
	printf("/*⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆     +:+ +:+         +:+   */\n");
	printf("/*⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿   +#+  +:+       +#+      */\n");
	printf("/*⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ +#+#+#+#+#+   +#+         */\n");
	printf("/*⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀      #+#    #+#           */\n");
	printf("/*⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀     ###   ########.fr     */\n");
	printf("/*⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀                           */\n");
	printf("/*⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀     By: vvaalant          */\n");
	printf("/*⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀     By: mrinkine          */\n");
	printf("/*⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀     _________             */\n");
	printf("/*⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀    |MINISHELL|            */\n");
	printf("/*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉                 ￣￣￣￣￣            */\n");
	printf("/* ******************************************************* */\n"DF);
	return ;
}
