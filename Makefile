# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:28:01 by kcw               #+#    #+#              #
#    Updated: 2023/04/25 17:43:35 by kcw              ###   ########.fr        #
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

############################################################################


SRC_FILES=minishell.c \
$(PARSING_SRC) \
$(BUILTINS_SRC) \
$(REDIRECTIONS_SRC) \

OBJECTS = $(SRC_FILES:.c=.o)
FT = ft

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT)
	cp ./$(LIBFT)/$(LIBFT_NAME) ./
	$(CC) $(CFLAGS) -L . -l $(FT) $(SRC_FILES) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
