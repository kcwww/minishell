# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkham <dkham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/09 23:30:46 by dkham             #+#    #+#              #
#    Updated: 2023/06/09 23:31:08 by dkham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

CFLAGS=-Wall -Wextra -Werror

LIBFT=libft
LIBFT_NAME=libft.a

AR=ar

ARFLAGS=rcsv

RM=rm -f

PARSING_PATH=parsing_src/
PARSING_FILES=check_quotation.c parsing.c parsing2.c free_all.c parsing3.c delete_single_quote.c delete_double_quote_heredoc.c \
replace_env.c delete_double_quote.c replace_env_quote.c is_env.c add_word.c parsing_utils.c make_simple_cmd.c env_utils.c
PARSING_SRC=$(addprefix $(PARSING_PATH), $(PARSING_FILES))

BUILTINS_PATH=builtins_src/
BUILTINS_FILES= builtin.c pwd/pwd.c echo/echo.c cd/cd.c cd/cd_utils.c env/env.c exit/exit.c export/export.c  export/export_utils.c export/export_utils_2.c unset/unset.c
BUILTINS_SRC=$(addprefix $(BUILTINS_PATH), $(BUILTINS_FILES))

REDIRECTIONS_PATH=redirections_src/
REDIRECTIONS_FILES=
REDIRECTIONS_SRC=$(addprefix $(REDIRECTIONS_PATH), $(REDIRECTIONS_FILES))

ERROR_PATH=error_src/
ERROR_FILES=error_str.c
ERROR_SRC=$(addprefix $(ERROR_PATH), $(ERROR_FILES))

INIT_PATH=init_src/
INIT_FILES=init_shell.c ft_envsplit.c find_value.c ft_strcmp.c signal_set.c
INIT_SRC=$(addprefix $(INIT_PATH), $(INIT_FILES))

SRC_FILES=minishell.c execute.c heredoc_redir.c heredoc_redir_utils.c process.c process_utils.c \
$(PARSING_SRC) \
$(BUILTINS_SRC) \
$(REDIRECTIONS_SRC) \
$(ERROR_SRC) \
$(INIT_SRC)

OBJECTS = $(SRC_FILES:.c=.o)

READLINE_LIB= -L$(shell brew --prefix readline)/lib/ -lreadline -L . -lft
READLINE_HEADER= -I . -I$(shell brew --prefix readline)/include/ -I include/

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT)
	cp ./$(LIBFT)/$(LIBFT_NAME) ./
	$(CC) $(CFLAGS) $(READLINE_HEADER) $(READLINE_LIB) $(SRC_FILES) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@

clean :
	make clean -C $(LIBFT)
	$(RM) $(OBJECTS)
	rm -rf $(OBJECTS)

fclean : clean
	make fclean -C $(LIBFT)
	rm -rf $(NAME) $(LIBFT_NAME)

re :
	make fclean
	make all

libft :
	make all -C $(LIBFT)/


.PHONY : all clean fclean re libft
