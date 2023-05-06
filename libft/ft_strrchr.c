/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:45:33 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/06 14:12:05 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	char	i;
	size_t	len;

	i = (char)c;
	len = ft_strlen(s) + 1;
	while (*s != 0)
		s++;
	while (len-- > 0)
	{
		if (*s == i)
			return ((char *)s);
		s--;
	}
	return (0);
}
