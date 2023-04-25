# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:28:01 by kcw               #+#    #+#              #
#    Updated: 2023/04/25 16:28:58 by kcw              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

CFLAGS=-Wall -Wextra -Werror

LIBFT=libft
LIBFT_NAME=libft.a

AR=ar

ARFLAGS=rcsv

RM=rm -f

SRC_FILES=test.c

OBJECTS = $(SRC_FILES:.c=.o)
FT = ft

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT)
	cp ./$(LIBFT)/$(LIBFT_NAME) ./
	$(CC) $(CFLAGS) -L . -l $(FT) $(SRC_FILES) -o $(NAME)

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
