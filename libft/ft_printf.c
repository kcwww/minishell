/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:17:37 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/24 20:19:01 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_format(const char *format, va_list ap)
{
	int	val;

	val = 1;
	if (*format == 0)
		return (-1);
	if (*format == 'c')
		val = ft_printchar(va_arg(ap, int), 1);
	else if (*format == 'd' || *format == 'i')
		val = ft_printint(va_arg(ap, int));
	else if (*format == 'x')
		val = ft_printhex(va_arg(ap, int), 1);
	else if (*format == 'X')
		val = ft_printhex(va_arg(ap, int), 2);
	else if (*format == 's')
		val = ft_printstr(va_arg(ap, char *));
	else if (*format == 'p')
		val = ft_printpointer(va_arg(ap, void *));
	else if (*format == 'u')
		val = ft_printuint(va_arg(ap, unsigned int));
	else if (*format == '%')
		val = ft_printchar('%', 1);
	if (val == -1)
		return (val);
	return (val);
}

static int	parse_str(const char *format, t_str *str, va_list ap)
{
	int		str_len;
	ssize_t	i;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			while (*format >= '0' && *format <= '9')
				format++;
			str_len = check_format(format, ap);
			if (str_len == -1)
				return (-1);
			str->len += str_len;
		}
		else
		{
			str->len++;
			i = ft_putchar(*format, 1);
			if (i == -1)
				return (i);
		}
		format++;
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_str	*str;
	int		len;

	va_start(ap, format);
	str = (t_str *)malloc(sizeof(t_str));
	if (str == 0)
	{
		va_end(ap);
		return (-1);
	}
	ft_memset(str, 0, sizeof(t_str));
	if (parse_str(format, str, ap) == -1)
		str->len = -1;
	va_end(ap);
	len = str->len;
	free(str);
	return (len);
}
