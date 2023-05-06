/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:20:04 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/06 14:10:09 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	idx;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	idx = dest_len;
	while (idx + 1 < dstsize && src[idx - dest_len])
	{
		dst[idx] = src[idx - dest_len];
		idx++;
	}
	if (dstsize)
		dst[idx] = 0;
	if (dest_len > dstsize || dstsize == 0)
		return (dstsize + src_len);
	return (dest_len + src_len);
}
