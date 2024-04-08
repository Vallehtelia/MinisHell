/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:50:13 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/05 19:55:33 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd(t_minishell *mshell)
{
	//int i = 0;
	//int x;
	//while(mshell->cmds[i] != NULL)
	//{
	//	x = 1;
	//	printf("cmd: %s\n", mshell->cmds[i]->cmd[0]);
	//	while(mshell->cmds[i]->cmd[x] != NULL)
	//	{
	//		printf("arg: %s\n", mshell->cmds[i]->cmd[x]);
	//		x++;
	//	}
	//	i++;
	//}
	if ((ft_strncmp(mshell->cmds[0]->cmd[0], "cd", 3) == 0))
	{
		//if(mshell->cmds[0]->cmd[1] != NULL)
		change_working_directory(mshell, mshell->cmds[0]->cmd[1]);
		return (1);
	}
	if ((ft_strncmp(mshell->cmds[0]->cmd[0], "exit", 5) == 0)
		&& mshell->cmds[0]->cmd[1] == NULL)
	{
		exit_and_free(mshell, 0);
		return (1);
	}
	else if ((ft_strncmp(mshell->cmds[0]->cmd[0], "exit", 5) == 0)
		&& mshell->cmds[0]->cmd[1] != NULL)
	{
		ft_printf("minisHell: exit: too many arguments\n");
		global_signal = 1;
		return (1);
	}
	else if (ft_strncmp(mshell->cmds[0]->cmd[0], "$?", 3) == 0)
	{
		ft_printf("minisHell: %d: command not found\n", global_signal);
		global_signal = 127;
		return (1);
	}
	else if (ft_strncmp(mshell->cmds[0]->cmd[0], "echo", 5) == 0
		&& mshell->env[0] == NULL)
	{
		if (ft_strncmp(mshell->cmds[0]->cmd[1], "-n", 3) == 0)
			ft_printf("%s", mshell->cmds[0]->cmd[2]);
		else
			ft_printf("%s\n", mshell->cmds[0]->cmd[1]);
		return (1);
	}
	return (0);
}

void	print_shrek(void)
{
	printf("\033[2J\033[H"); // clears screen
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
	printf("/*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉                                       */\n");
	printf("/* ******************************************************* */\n"DF);
	return ;
}
