# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 14:14:33 by chanwoki          #+#    #+#              #
#    Updated: 2023/04/25 16:31:05 by kcw              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = ft_bzero.c ft_memset.c ft_strlen.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_isalpha.c \
ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
ft_atoi.c ft_strnstr.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_strdup.c ft_strjoin.c \
ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c \
ft_substr.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
ft_printf.c ft_printhex.c ft_printpointer.c ft_itoahex.c ft_itop.c \
ft_printstr.c ft_printint.c ft_printchar.c ft_printuint.c ft_uitoa.c ft_putchar.c ft_putstr.c \
get_next_line.c get_next_line_bonus.c get_next_line_utils.c get_next_line_utils_bonus.c \
ft_lstadd_front.c ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c

OBJECTS = $(SRC_FILES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADER = .

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar rscv $(NAME) $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
