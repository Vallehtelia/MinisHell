/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:10:07 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/24 16:30:30 by vvaalant         ###   ########.fr       */
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
}	t_commands;

typedef struct s_minishell
{
	t_commands	**cmd;
	char		*input_cmd;
	int			num_of_pipes;
	char 		*working_directory;
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

#endif
