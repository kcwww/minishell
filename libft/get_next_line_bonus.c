/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:00:36 by chanwoki          #+#    #+#             */
/*   Updated: 2023/01/01 16:58:43 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_str(char **line, char **buf)
{
	if (line != NULL)
	{
		if (*line != NULL)
		{
			free(*line);
			*line = NULL;
		}
	}
	if (buf != NULL)
	{
		if (*buf != NULL)
		{
			free(*buf);
			*buf = NULL;
		}
	}
}

char	*ft_read(int fd, char *line)
{
	char	*buf;
	ssize_t	len;

	len = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	buf[0] = 0;
	while (len != 0 && gnl_strchr(buf, '\n') == NULL)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
		{
			free_str(&line, &buf);
			return (NULL);
		}
		if (len != 0)
		{
			buf[len] = 0;
			line = gnl_strjoin(line, buf);
		}
	}
	free_str(NULL, &buf);
	return (line);
}

char	*get_line(char *line)
{
	char	*g_line;
	int		len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		len++;
	g_line = (char *)malloc(sizeof(char) * (len + 1));
	if (g_line == NULL)
		return (NULL);
	gnl_strlcpy(g_line, line, len + 1);
	return (g_line);
}

char	*next_line(char *line)
{
	char	*n_line;
	int		len;
	int		line_len;

	len = 0;
	line_len = gnl_strlen(line);
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		len++;
	if (line_len == len)
	{
		free_str(&line, NULL);
		return (NULL);
	}
	n_line = (char *)malloc(sizeof(char) * (line_len - len + 1));
	if (n_line == NULL)
	{
		free_str(&line, NULL);
		return (NULL);
	}
	gnl_strlcpy(n_line, line + len, line_len - len + 1);
	free_str(&line, NULL);
	return (n_line);
}

char	*get_next_line(int fd)
{
	char		*re;
	static char	*line[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = ft_read(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	re = get_line(line[fd]);
	if (re == NULL)
		return (NULL);
	line[fd] = next_line(line[fd]);
	return (re);
}
