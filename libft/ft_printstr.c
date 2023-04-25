/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:55:37 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 20:23:29 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *str)
{
	char	*re;
	size_t	len;
	ssize_t	i;

	if (str == 0)
	{
		re = "(null)";
		str = re;
	}
	i = ft_putstr(str, 1);
	if (i == -1)
		return (i);
	len = ft_strlen(str);
	return (len);
}
