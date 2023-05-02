/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/05/02 22:25:05 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//void    echo(char **args, t_execute *execute) // 일단 무조건 2차원 배열 받는다고 가정

// 오류 처리
// $ echo -n -n -n -n -nnn -nnnn -nnnnm Hello
// -nnnnm Hello // 이렇게 출력되어야 함
// 현재: -n -n -n -nnn -nnnn -nnnnm Hello

// $ echo -n -n -n -n -nnn -nnnn -nnnnm -nHello
// -nnnnm -nHello // 이렇게 출력되어야 함
// 현재: -n -n -n -nnn -nnnn -nnnnm -nHello

void	echo(char **args, t_execute *execute)
{
	int	i;
	int	j;
	int	n_flag;

	i = 1;
	j = 1;
	n_flag = 0;
	// if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	// {
	// 	n_flag = 1;
	// 	i++;
	// }
	
	// skip if : -n or multiple "n"s attached to the first argument
	// ex) $ echo -n -n -n -n -nnn -nnnn Hello
	// if -n is combined with other characters, it is not skipped
	// ex) $ echo -n -n -nnn -nnnnm Hello
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		// use loop to check if args contains only "n"s
		// ex) $ echo -nnn
		while (args[i][j])
		{
			if (ft_strchr(args[i], 'n') == NULL)
				break ;
			j++;
		}
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], execute->fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", execute->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", execute->fd_out);
}
