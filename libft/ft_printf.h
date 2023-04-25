/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:49:59 by chanwoki          #+#    #+#             */
/*   Updated: 2023/01/01 16:37:34 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef struct s_str
{
	char	*str;
	int		len;
}	t_str;

int		ft_printf(const char *format, ...);
int		ft_printhex(unsigned int num, int i);
int		ft_printpointer(void *ptr);
char	*ft_itoahex(unsigned int n, int i);
int		ft_printint(int num);
char	*ft_itop(unsigned long long n);
int		ft_printstr(char *str);
int		ft_printchar(char c, int fd);
int		ft_printuint(unsigned int num);
char	*ft_uitoa(unsigned int n);
ssize_t	ft_putchar(char c, int fd);
ssize_t	ft_putstr(char *s, int fd);

#endif
