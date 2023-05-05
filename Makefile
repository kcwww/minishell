# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:28:01 by kcw               #+#    #+#              #
#    Updated: 2023/05/05 17:15:35 by chanwoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

CFLAGS=-Wall -Wextra -Werror

LIBFT=libft
LIBFT_NAME=libft.a

AR=ar

ARFLAGS=rcsv

RM=rm -f

############################################################################
PARSING_PATH=parsing_src/
PARSING_FILES=
PARSING_SRC=$(addprefix $(PARSING_PATH), $(PARSING_FILES))


BUILTINS_PATH=builtins_src/
BUILTINS_FILES=
BUILTINS_SRC=$(addprefix $(BUILTINS_PATH), $(BUILTINS_FILES))

REDIRECTIONS_PATH=redirections_src/
REDIRECTIONS_FILES=
REDIRECTIONS_SRC=$(addprefix $(REDIRECTIONS_PATH), $(REDIRECTIONS_FILES))

ERROR_PATH=error_src/
ERROR_FILES=error_str.c
ERROR_SRC=$(addprefix $(ERROR_PATH), $(ERROR_FILES))

INIT_PATH=init_src/
INIT_FILES=init_shell.c ft_envsplit.c
INIT_SRC=$(addprefix $(INIT_PATH), $(INIT_FILES))

############################################################################


SRC_FILES=minishell.c \
$(PARSING_SRC) \
$(BUILTINS_SRC) \
$(REDIRECTIONS_SRC) \
$(ERROR_SRC) \
$(INIT_SRC) 

OBJECTS = $(SRC_FILES:.c=.o)


########

READLINE_LIB= -lreadline -L${HOME}/.brew/opt/readline/lib -L . -lft
READLINE_HEADER= -I . -I${HOME}/.brew/opt/readline/include -I include/

########

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
