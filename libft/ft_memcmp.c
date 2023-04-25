/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:42:00 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/13 17:53:56 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*m1;
	unsigned char	*m2;

	if (s1 == 0 && s2 == 0)
		return (0);
	i = 0;
	m1 = (unsigned char *)s1;
	m2 = (unsigned char *)s2;
	while (i < n)
	{
		if (*m1 != *m2)
			return (*m1 - *m2);
		m1++;
		m2++;
		i++;
	}
	return (0);
}
