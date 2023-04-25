/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:41:54 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 19:04:07 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*re;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > 0 && ft_strchr(set, s1[end - 1]))
		end--;
	if (start > end)
		return ((char *)ft_calloc(1, sizeof(char)));
	re = (char *)malloc(sizeof(char) * (end - start + 1));
	if (re == 0)
		return (0);
	ft_strlcpy(re, s1 + start, end - start + 1);
	return (re);
}
