/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:11:56 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 19:22:28 by chanwoki         ###   ########.fr       */
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
		n /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int	len;
	unsigned int	num;
	char			*re;

	len = check_len(n);
	num = n;
	n = 0;
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (re == 0)
		return (0);
	re[len] = 0;
	len--;
	while (len >= n)
	{
		re[len] = (num % 10) + '0';
		num /= 10;
		if (len == 0)
			break ;
		len--;
	}
	return (re);
}
