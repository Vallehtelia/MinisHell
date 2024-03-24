NAME = minishell
LIBFT = ./libft
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./sources/

# source files here
SRC_FILES = minishell.c valle.c matti.c exit_and_free.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

all: $(LIBFT)/libft.a $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32m" -------Building minishell------ "\033[0m"
	@$(CC) $(OBJ) -o $(NAME) -L$(LIBFT) -lft -lreadline

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
