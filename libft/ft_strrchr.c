/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:45:33 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 19:03:23 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
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
