/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:39:40 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 16:24:53 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	mem_len;
	size_t	src_len;

	src_len = ft_strlen(s);
	if (start >= src_len)
	{
		str = (char *)ft_calloc(1, sizeof(char));
		if (str == 0)
			return (0);
		return (str);
	}
	mem_len = src_len - start;
	if (len > mem_len)
		len = mem_len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
