/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:37:28 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 18:40:28 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src || len == 0)
		return (dst);
	i = 0;
	if (src - dst > 0 && (size_t)(src - dst) < len)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
		return (dst);
	}
	else if (dst - src > 0 && (size_t)(dst - src) < len)
	{
		i = len;
		while (i-- > 0)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
