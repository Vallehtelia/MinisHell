/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:10:07 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/28 01:27:24 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define DEFAULT "\033[0m"

typedef struct s_commands
{
	char	**cmd;
	bool	output_to_pipe;
	int 	cmd_lenght;
}	t_commands;

typedef struct s_minishell
{
	t_commands	**cmds;
	char		*input_cmd; 		// prompt text
	int			num_of_pipes;
	int			num_of_cmds;
	char		*working_directory;	//current working directory
}	t_minishell;

/* Functions here */
int		main(void);
// void	useinput(char *str);
void	parse_command(t_minishell *mshell);
void	matti(t_minishell *mshell);
void	matti_set(t_minishell *mshell);
void	valle(t_minishell *mshell);
void	valle_set(t_minishell *mshell);

void 	exit_and_free(t_minishell *mshell, int errno);
void 	free_workingdir(t_minishell *mshell);
void 	change_working_directory(t_minishell *mshell, char *path);
void	free_commands(t_minishell *mshell);


#endif
