/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:13:15 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 18:56:04 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*re;

	len = ft_strlen(s1);
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (re == 0)
		return (0);
	ft_strlcpy(re, s1, len + 1);
	return (re);
}
