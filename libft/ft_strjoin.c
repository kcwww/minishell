/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:24:48 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 18:38:29 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*re;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	re = (char *)malloc(sizeof(char) * (i + j + 1));
	if (re == 0)
		return (0);
	ft_strlcpy(re, s1, i + 1);
	ft_strlcpy(re + i, s2, j + 1);
	return (re);
}
