/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:54:48 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/10 19:22:33 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dptr;
	unsigned char	*sptr;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	dptr = (unsigned char *)dst;
	sptr = (unsigned char *)src;
	while (i < n)
	{
		dptr[i] = sptr[i];
		i++;
	}
	return (dptr);
}
