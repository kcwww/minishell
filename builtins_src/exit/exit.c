/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:42:54 by dkham             #+#    #+#             */
/*   Updated: 2023/05/02 21:59:10 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// fucntion name: exit
// reproduce the behavior of exit() in bash (with no options)

void	cmd_exit(char **args, t_execute *execute)
{
	int i;

	i = 0;
	if (args[1])
	{
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0)
			{
				ft_putstr_fd("exit\n", execute->fd_out);
				ft_putstr_fd("minishell: exit: ", execute->fd_out);
				ft_putstr_fd(args[1], execute->fd_out);
				ft_putstr_fd(": numeric argument required\n", execute->fd_out);
				exit(255);
			}
			i++;
		}
		if (args[2])
		{
			ft_putstr_fd("exit\n", execute->fd_out);
			ft_putstr_fd("minishell: exit: too many arguments\n", execute->fd_out);
			exit(1);
		}
		else
			exit(ft_atoi(args[1]));
	}
	else
		exit(0);
}
