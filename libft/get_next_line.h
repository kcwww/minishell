/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:00:34 by chanwoki          #+#    #+#             */
/*   Updated: 2023/02/25 19:18:16 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

char	*get_next_line(int fd);
char	*gnl_strchr(char *s, int c);
size_t	gnl_strlen(char *s);
size_t	gnl_strlcpy(char *dst, char *src, size_t dstsize);
char	*gnl_strdup(char *s1);
char	*gnl_strjoin(char *s1, char *s2);

#endif
