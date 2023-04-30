/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/04/30 19:53:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//void    echo(char **args, t_execute *execute) // 일단 무조건 2차원 배열 받는다고 가정
void	echo(char **args)
{
	int	i;
	int	n;

	// initialize variables
	i = 1;
	n = 0;
	// check for -n flag
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n = 1;
		i++;
	}
	// print args
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	// print a newline if -n is not set
	if (!n)
		ft_putchar_fd('\n', 1);
}

// int main(int argc, char **argv)
// {
// 	// use argv
// 	(void)argc;
// 	// initialize variables

// }
