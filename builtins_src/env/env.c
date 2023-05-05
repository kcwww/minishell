/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:30:03 by dkham             #+#    #+#             */
/*   Updated: 2023/05/05 19:08:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// env with no options or arguments

void	env(t_execute *execute)
{
	t_env	*env;

	env = execute->env;
	while (env)
	{
		if (env->value)
		{
			if (ft_strlen(env->value) == 0)
			{
				env = env->next;
				continue ;
			}
			ft_putstr_fd(env->key, execute->fd_out);
			ft_putstr_fd("=", execute->fd_out);
			ft_putendl_fd(env->value, execute->fd_out);
		}
		env = env->next;
	}
}
