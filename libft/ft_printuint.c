/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:58:22 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 19:23:58 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printuint(unsigned int num)
{
	char	*re;
	int		len;

	re = ft_uitoa(num);
	if (re == 0)
		return (-1);
	len = ft_printstr(re);
	free(re);
	return (len);
}
