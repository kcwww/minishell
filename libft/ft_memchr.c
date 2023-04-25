/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:27:22 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/13 17:41:21 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chr;
	unsigned char	find;
	size_t			i;

	chr = (unsigned char *)s;
	find = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*chr == find)
			return ((void *)chr);
		chr++;
		i++;
	}
	return ((void *)0);
}
