/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:17:37 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 15:59:05 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printhex(unsigned int num, int i)
{
	char	*hex;
	int		len;

	hex = ft_itoahex(num, i);
	if (hex == 0)
		return (-1);
	len = ft_printstr(hex);
	free(hex);
	return (len);
}
