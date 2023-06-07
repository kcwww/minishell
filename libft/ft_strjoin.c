/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:24:48 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/07 20:17:48 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*re;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	re = (char *)malloc(sizeof(char) * (i + j + 1));
	if (re == NULL)
		return (NULL);
	re[i + j] = 0;
	ft_strlcpy(re, s1, i + 1);
	ft_strlcpy(re + i, s2, j + 1);
	return (re);
}
