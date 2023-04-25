/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoahex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:20 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 14:40:22 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	check_len(unsigned int n)
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

char	*ft_itoahex(unsigned int n, int i)
{
	unsigned int	len;
	unsigned int	num;
	char			*re;
	char			*hex;

	if (i == 1)
		hex = "0123456789abcdef";
	else if (i == 2)
		hex = "0123456789ABCDEF";
	len = check_len(n);
	num = n;
	n = 0;
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (re == 0)
		return (0);
	re[len] = 0;
	while (len-- > n)
	{
		re[len] = hex[(num % 16)];
		num /= 16;
	}
	return (re);
}
