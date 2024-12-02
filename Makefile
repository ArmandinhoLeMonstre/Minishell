NAME = minishell

LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/Users/armitite/homebrew/opt/readline/include -g3
MFLAGS = -lreadline -L/Users/armitite/homebrew/opt/readline/lib -g3 #-fsanitize=address -g

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = main pipe_noding pipe_noding_utils pipe_parsing file_parsing panic free_fct unexpected_token cmd_parsing stock_and_open_file \
quote_check heredoc pipe_in_commas pipe_in_commas_utils expander expander_utils expander_utils2 cmd_parsing_commas clean_space_commas_utils \
clean_space_commas cd cd_utils builtins env export_sort export_utils export unset signals exit pwd exec_bis echo main_global_utils build_env

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

HEAD = ./include/

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
	@$(CC) $(CFLAGS) $(MFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
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