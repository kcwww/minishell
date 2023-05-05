/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/05 13:37:03 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin(char **args, t_execute *execute)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo(args, execute);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd();
	// else if (ft_strncmp(args[0], "cd", 3) == 0)
	// 	cd(args, execute);
	// else if (ft_strncmp(args[0], "export", 7) == 0)
	// 	export(args);
	// else if (ft_strncmp(args[0], "unset", 6) == 0)
	// 	unset(args);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		env(execute);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		cmd_exit(args, execute);
	else
		ft_putendl_fd("minishell: command not found", 1);
}
