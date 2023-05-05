/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:30:03 by dkham             #+#    #+#             */
/*   Updated: 2023/05/05 12:52:41 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// env with no options or arguments

void	env(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute->env[i])
	{
		ft_putendl_fd(execute->env[i], execute->fd_out);
		i++;
	}
}
