/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:32:37 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 15:59:26 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printpointer(void *ptr)
{
	unsigned long long	p;
	char				*re;
	int					len;

	p = (unsigned long long)ptr;
	re = ft_itop(p);
	if (re == 0)
		return (-1);
	len = ft_printstr(re);
	free(re);
	return (len);
}
