NAME = minishell

LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MFLAGS = -lreadline -Wall -Wextra -Werror

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = main pipe_noding pipe_parsing infile_parsing panic panic_parsing_fct free_fct unexpected_token cmd_parsing \
shell_execution pid_executions quote_check

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

HEAD = ./include/

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
	@$(CC) $(MFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[1;32m./minishell created\n"

$(LIBFT)	:
	@echo "\033[0;33m\nCOMPILING LIBFT\n"
	@make -C ./libft
	@echo "\033[1;32mLIBFT created\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

clean :
	$(RM) ./libft/*.o
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME)

re : fclean all