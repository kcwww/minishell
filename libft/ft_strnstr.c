/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:02:07 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/13 17:26:40 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	f_i;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			f_i = 0;
			while (1)
			{
				if (needle[f_i] == 0)
					return ((char *)&haystack[i]);
				if (!(haystack[i + f_i] == needle[f_i]))
					break ;
				if (i + f_i >= len)
					break ;
				f_i++;
			}
		}
		i++;
	}
	return (0);
}
