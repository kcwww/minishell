/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:00:19 by chanwoki          #+#    #+#             */
/*   Updated: 2023/01/01 17:00:03 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_strchr(char *s, int c)
{
	char	i;
	int		idx;

	if (s == NULL)
		return (NULL);
	i = (char)c;
	idx = 0;
	while (s[idx] != i)
	{
		if (s[idx] == 0)
			return (NULL);
		idx++;
	}
	return ((char *)&s[idx]);
}

size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	src_size;
	size_t	idx;

	if (src == NULL)
		return (0);
	idx = 0;
	src_size = gnl_strlen(src);
	while (src[idx] && idx + 1 < dstsize)
	{
		dst[idx] = src[idx];
		idx++;
	}
	if (dstsize != 0)
		dst[idx] = 0;
	return (src_size);
}

char	*gnl_strdup(char *s1)
{
	size_t	len;
	char	*re;

	len = gnl_strlen(s1);
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (re == NULL)
		return (NULL);
	gnl_strlcpy(re, s1, len + 1);
	return (re);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*re;
	size_t	i;
	size_t	j;

	i = gnl_strlen(s1);
	j = gnl_strlen(s2);
	re = (char *)malloc(sizeof(char) * (i + j + 1));
	if (re == NULL)
		return (NULL);
	re[i + j] = 0;
	gnl_strlcpy(re, s1, i + 1);
	if (s1 != NULL)
		free(s1);
	gnl_strlcpy(re + i, s2, j + 1);
	return (re);
}
