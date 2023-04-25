/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:36:30 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 19:28:56 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putstr(char *s, int fd)
{
	int		i;
	ssize_t	c;

	i = 0;
	while (s[i])
	{
		c = ft_putchar(s[i], fd);
		if (c == -1)
			return (c);
		i++;
	}
	return (c);
}
