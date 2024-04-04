/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:58 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/04 18:46:16 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_signal = 0;

int	hardcode(t_minishell *mshell, char *input)
{
	if (ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
	{
		free(input);
		exit_and_free(mshell, 0);
	}
	if (ft_strncmp(input, "$?", 3) == 0)
	{
		add_history(input);
		free(input);
		printf("minisHell: %d: command not found\n", global_signal);
		global_signal = 127;
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

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	mshell;

	mshell = (t_minishell){};
	av = NULL;
	ac = 0;
	print_shrek();
	mshell.env = parse_env(envp, -1, 0);
	while (1)
	{
		matti_set(&mshell);
		input = readline(mshell.prompt_text);
		if (!input)
			break ;
		free_workingdir(&mshell);
		if(hardcode(&mshell, input))
			continue ;
		global_signal = 0;
		mshell.input_cmd = input;
		matti(&mshell);
		valle(&mshell);
		//printf("KUMMAN VIKA!!!\n");
		add_history(input);
		free(input);
	}
	return (0);
}
