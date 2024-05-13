NAME = minishell
LIBFT = ./libft
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./sources/

READ_LINE_DIR = /Users/$(USER)/.brew/Cellar/readline/8.2.10/lib

# source files here
SRC_FILES = minishell.c valle.c matti.c exit_and_free.c cmd_split.c \
			environment.c hardcodes.c builtins.c redirections.c \
			redir_utils.c signal.c signal2.c exitcode.c env_values.c \
			env_value_utils.c env_value_utils2.c env_value_utils3.c \
			forks.c cmd_utils.c cmds.c parsing.c parsing_utils.c \
			exits.c echo.c cd.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

all: $(LIBFT)/libft.a $(READ_LINE_DIR)/libreadline.a $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32m" -------Building minishell------ "\033[0m"
	@$(CC) $(OBJ) -o $(NAME) -L$(LIBFT) -lft -L $(READ_LINE_DIR) -lreadline

$(LIBFT)/libft.a:
	@make -C $(LIBFT)
	@make bonus -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@echo "\033[0;32m" ------------Cleaning----------- "\033[0m"
	@rm -f $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	@echo "\033[0;32m" ---------Deep cleaning--------- "\033[0m"
	@rm -f $(NAME)
	@$(RM) $(LIBFT)/libft.a
	@$(RM) $(LIBFT)/.bonus

re: fclean all
