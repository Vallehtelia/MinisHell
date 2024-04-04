/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:10:07 by vvaalant          #+#    #+#             */
/*   Updated: 2024/04/04 14:06:51 by vvaalant         ###   ########.fr       */
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

# define MAX_ARGS 10

typedef struct s_commands
{
	char	**cmd;
	bool	output_to_pipe;
	int		cmd_lenght;
}	t_commands;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_minishell
{
	t_commands	**cmds;
	t_env		**env;
	char		**av;
	int			ac;
	char		*cmd_to_split;
	char		*input_cmd; 		// prompt text
	char		*prompt_text;
	int			num_of_pipes;
	int			num_of_cmds;
	char		*working_directory;	//current working directory
}	t_minishell;

/* Functions here */
int		main(int ac, char **av, char **envp);
// void	useinput(char *str);
void	matti(t_minishell *mshell);
void	matti_set(t_minishell *mshell);
void	valle(t_minishell *mshell);

void	exit_and_free(t_minishell *mshell, int errno);
void	free_workingdir(t_minishell *mshell);
void	change_working_directory(t_minishell *mshell, char *path);

/* command parsing */
int		parse_command(t_minishell *mshell);
char	**get_cmd(const char *cmd);
void	free_commands(t_minishell *mshell);

/* environment init */
t_env	**parse_env(char **envp, int i, int keylen);

/* command execution */
void	run_commands(t_minishell *mshell);
void	execute_cmd(char **cmd, t_env **env);
char	*find_path(char *cmd, t_env **env, int i);
char	**env_to_char_array(t_env **env);
char	*get_env_value(t_env **env, char *key);
void	error_str(char *av, int n);

#endif
