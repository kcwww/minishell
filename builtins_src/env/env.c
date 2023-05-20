/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:30:03 by dkham             #+#    #+#             */
/*   Updated: 2023/05/20 17:54:42 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(t_shell *my_shell)
{
	t_env	*env;

	env = my_shell->env;
	while (env)
	{
		if (env->value)
		{
			if (ft_strlen(env->value) == 0)
			{
				env = env->next;
				continue ;
			}
			ft_putstr_fd(env->key, my_shell->fd_out);
			ft_putstr_fd("=", my_shell->fd_out);
			ft_putendl_fd(env->value, my_shell->fd_out);
		}
		env = env->next;
	}
}
