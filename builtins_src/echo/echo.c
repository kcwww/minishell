/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/05/02 20:43:48 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//void    echo(char **args, t_execute *execute) // 일단 무조건 2차원 배열 받는다고 가정
void    echo(char **args, t_execute *execute)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
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

// int main(int argc, char **argv)
// {
// 	// use argv
// 	(void)argc;
// 	// initialize variables

// }
