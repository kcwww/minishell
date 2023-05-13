/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:30:03 by dkham             #+#    #+#             */
/*   Updated: 2023/05/13 13:05:09 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(t_shell *myshell)
{
	t_env	*env;

	env = myshell->env;
	while (env)
	{
		if (env->value)
		{
			if (ft_strlen(env->value) == 0)
			{
				env = env->next;
				continue ;
			}
			ft_putstr_fd(env->key, myshell->fd_out);
			ft_putstr_fd("=", myshell->fd_out);
			ft_putendl_fd(env->value, myshell->fd_out);
		}
		env = env->next;
	}
}
