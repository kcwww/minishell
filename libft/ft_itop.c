/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:37:03 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 14:52:40 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	check_len(unsigned long long n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

char	*ft_itop(unsigned long long n)
{
	unsigned int		len;
	unsigned long long	num;
	char				*re;
	char				*hex;

	hex = "0123456789abcdef";
	len = check_len(n) + 2;
	num = n;
	n = 2;
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (re == 0)
		return (0);
	re[len] = 0;
	while (len-- > n)
	{
		re[len] = hex[(num % 16)];
		num /= 16;
	}
	re[0] = '0';
	re[1] = 'x';
	return (re);
}
