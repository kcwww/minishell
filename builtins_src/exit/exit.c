/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:42:54 by dkham             #+#    #+#             */
/*   Updated: 2023/05/07 12:31:28 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_exit(t_execute *execute)
{
	int		exit_code;
	char	*error_message;

	error_message = validate_exit_args(execute, &exit_code);
	if (error_message)
	{
		ft_putstr_fd("exit\n", execute->fd_out);
		ft_putstr_fd("minishell: exit: ", execute->fd_out);
		ft_putstr_fd(error_message, execute->fd_out);
		ft_putstr_fd("\n", execute->fd_out);
	}
	else
		exit(exit_code);
}

char	*validate_exit_args(t_execute *execute, int *exit_code)
{
	int	i;

	i = 0;
	if (execute->args[1])
	{
		while (execute->args[1][i])
		{
			if (ft_isdigit(execute->args[1][i]) == 0)
			{
				*exit_code = 255;
				return ("numeric argument required");
			}
			i++;
		}
		if (execute->args[2])
		{
			*exit_code = 1;
			return ("too many arguments");
		}
		else
			*exit_code = ft_atoi(execute->args[1]);
	}
	else
		*exit_code = 0;
	return (NULL);
}
