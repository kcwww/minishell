/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:25:32 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 15:59:17 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printint(int num)
{
	char	*re;
	int		len;

	re = ft_itoa(num);
	if (re == 0)
		return (-1);
	len = ft_printstr(re);
	free(re);
	return (len);
}
