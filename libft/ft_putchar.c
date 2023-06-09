/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:29:45 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 19:28:52 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putchar(char c, int fd)
{
	ssize_t	i;

	i = write(fd, &c, 1);
	if (i == -1)
		return (i);
	return (i);
}
