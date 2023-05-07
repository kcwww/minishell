/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/07 12:54:02 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin(t_execute *execute)
{
	if (ft_strncmp(execute->args[0], "echo", 5) == 0)
		echo(execute);
	else if (ft_strncmp(execute->args[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(execute->args[0], "cd", 3) == 0)
		cd(execute);
	else if (ft_strncmp(execute->args[0], "export", 7) == 0)
		export(execute);
	else if (ft_strncmp(execute->args[0], "unset", 6) == 0)
		unset(execute);
	else if (ft_strncmp(execute->args[0], "env", 4) == 0)
		env(execute);
	else if (ft_strncmp(execute->args[0], "exit", 5) == 0)
		cmd_exit(execute);
	else
		ft_putendl_fd("minishell: command not found", 1);
}
