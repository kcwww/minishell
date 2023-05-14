/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:21:06 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/14 12:45:41 by kcw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    sigint_handler(int signo)
{
    if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void    init_signal()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

void    init_env(t_env *my_env, char **env)
{
    int i;

    my_env->next = NULL;
    i = 0;
    while (env[i])
    {
        my_env->var = ft_envsplit(env[i]);
        my_env->param = my_env->var[0];
        my_env->value = my_env->var[1];
        i++;
        if (env[i])
            my_env->next = (t_env *)malloc(sizeof(t_env)); // NULL GUARD
        my_env = my_env->next;
    }
}

void	init_shell(t_shell *my_shell, char **env)
{
	my_shell->env = (t_env *)malloc(sizeof(t_env)); // NULL GUARD

	init_env(my_shell->env, env);

	init_signal();
}
