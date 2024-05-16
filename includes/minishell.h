/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:10:07 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 21:37:46 by vvaalant         ###   ########.fr       */
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
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <glob.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <termios.h>

# define GR "\033[0;32m"
# define CYAN "\033[0;36m"
# define DF "\033[0m"

// Singnal defines //
# define DEFAULT 0
# define IN_HEREDOC 666
# define STOP_HEREDOC 555
# define IN_CMD 66

typedef struct s_env_values
{
	int	i;
	int	l;
	int	j;
	int	k;
	int	cmd_chk;
}	t_env_values;

typedef struct s_tempsort
{
	char				*key;
	char				*value;
	bool				have_value;
	struct s_tempsort	*next;
	struct s_tempsort	*prev;
}	t_tempsort;

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
	bool	have_value;
}	t_env;

typedef struct s_minishell
{
	t_commands	**cmds;
	t_env		**env;
	pid_t		last_pid;
	char		**av;
	int			ac;
	int			exit_code;
	char		*cmd_to_split;
	char		*input_cmd;		// prompt text
	char		*prompt_text;
	char		*redir_output;
	//char		*old_pwd;
	int			num_of_pipes;
	int			num_of_cmds;
	bool		ends_or_starts_with_pipe;
	char		*working_directory;	//current working directory
}	t_minishell;

/* Functions here */
int			main(int ac, char **av, char **envp);

// void	useinput(char *str);
void		matti(t_minishell *mshell);
void		matti_set(t_minishell *mshell);
void		valle(t_minishell *mshell);

void		exit_and_free(t_minishell *mshell, int errnum);
void		free_workingdir(t_minishell *mshell);
void		change_working_directory(t_minishell *mshell, char *path);
void		free_arr(char **arr, int i);

/* command parsing */
int			parse_command(t_minishell *mshell);
char		**get_cmd(const char *cmd);
void		free_commands(t_minishell *mshell);
int			count_quotes(char *input_cmd);
void		remove_quotes_from_cmds(t_minishell *mshell);
void		remove_quotes(char **cmd, int j);
const char	*skip_spaces(const char *str);
char		*copy_arg(const char *cmd, char **arg_out, int j, char *arg);

/* environment init */
t_env		**parse_env(char **envp, int i);
t_env		*allocate_env(char *key, char *value, int parsing);
int			env_count(char **envp);

/* Builtins */
int			check_builtins(t_minishell *mshell, char **cmd);
int			run_exit(t_minishell *mshell, char **cmd, int i, int res);
int			handle_env_var(t_minishell *mshell, char *env);
int			change_value(t_minishell *mshell, int i, int l, int echo_check);
int			handle_values(t_minishell *mshell, int i, int l, int cmd_check);
char		*change_value_value(char *cmd, char *value, int j, int k);
int			confirm_env_chars(t_minishell *mshell, int i, int l, int k);
int			skip_env_chars(t_minishell *mshell, int i, int l, int j);
int			run_exit(t_minishell *mshell, char **cmd, int i, int res);
int			echo(t_minishell *mshell, char **cmd, int i);
void		sort_list(t_tempsort *head, char *key, char *value, \
					bool have_value);
t_tempsort	*create_list(t_minishell *mshell);
void		free_list(t_tempsort *head);

/* command execution */
void		run_commands(t_minishell *mshell, int i, int fd_in);
void		execute_cmd(t_minishell *mshell, char **cmd, t_env **env);
char		*find_path(char *cmd, t_env **env, int i);
int			check_path(t_minishell *mshell, char *cmd);
char		**env_to_char_array(t_env **env);
char		*get_env_value(t_env **env, char *key);
void		error_str(t_minishell *mshell, char *av, char *str, int n);
void		free_env_arr(t_minishell *mshell, char **env_arr, \
						char *path, char **cmd);
int			check_cmd(t_minishell *mshell);
int			check_exit_code(t_minishell *mshell, int i, int l);
void		count_pipes(t_minishell *mshell, char *input_cmd, \
						int i, bool in_quote);
int			ft_cmdlen(char *str);
int			handle_pipe_end(t_minishell *mshell, char *input);
bool		check_env_inside_squotes(t_minishell *mshell, char **cmd, \
									int i, int k);
void		remove_quotes(char **cmd, int j);

/* redirections */
int			check_redirections(t_minishell *mshell, char **cmd, \
								int j, int output);
int			check_valid_redir(t_minishell *mshell);
int			check_input_redirection(t_minishell *mshell, char **cmd, int j);
int			check_output_redirection(t_minishell *mshell, char **cmd, int j);
void		nullify_cmd(t_minishell *mshell, char **cmd, int i);
void		redir_input_heredoc(t_minishell *mshell, char **cmd, \
								int i, char *l);
void		handle_redir_input(t_minishell *mshell, char **cmd, int i);
void		signal_handler(t_minishell *mshell);
void		handle_sigquit(int sig);
void		print_shrek(void);

/* matin sekoilua */
void		add_env(t_minishell *mshell, char *key, char *value);
void		free_env(t_minishell *mshell);
bool		check_if_env_exists(t_env **env, char *key);
int			set_env_value(t_env **env, char *key, char *value, int i);
void		print_env(t_minishell *mshell);
void		delete_env(t_minishell *mshell, char *key);
int			handle_identifier(t_minishell *mshell, char *key, \
							char *value, int equals);
bool		check_indentifier(char *key);
void		parse_env_helper(t_env **env_vars, char *env_entry, \
							char *del_po, int i);
void		export_env_helper(t_minishell *mshell, char **cmd, int i);
void		export_env(t_minishell *mshell, char **cmd);
void		print_env_export(t_minishell *mshell);
char		*clean_value(char *value, int i, int x);
int			parse_quotes(char *string);
void		set_old_pwd(t_minishell *mshell);
void		set_working_directory(t_minishell *mshell);
int			handle_export(t_minishell *mshell);

/* signals */
void		caret_switch(int on);
void		sigquit_handler(int sig);
int			handle_signal(void);
void		rl_replace_line(const char *text, int clear_undo);
void		signal_basic(void);
void		signal_heredoc(void);
void		signal_execute(void);
void		signal_default(void);
void		signal_in_execve(void);
void		signal_no_pipe_end(void);
//void		handle_sigint(int sig);

#endif
