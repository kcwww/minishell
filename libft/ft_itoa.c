/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:20 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 14:56:25 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len(int n)
{
	int	len;

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

char	*ft_itoa(int n)
{
	int		len;
	long	num;
	char	*re;

	len = check_len(n);
	num = (long)n;
	n = 0;
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (re == 0)
		return (0);
	re[len] = 0;
	if (num < 0)
	{
		re[0] = '-';
		num = -num;
		n = 1;
	}
	while (len-- > n)
	{
		re[len] = (num % 10) + '0';
		num /= 10;
	}
	return (re);
}
