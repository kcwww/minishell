/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:34:54 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/27 13:29:20 by kcw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	init_signal()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_env(t_env *my_env, char **env)
{
	int 	i;
	char	**str;

	my_env->next = NULL;
	i = 0;
	while (env[i])
	{
		str = ft_envsplit(env[i]);
		my_env->key = str[0];
		my_env->value = str[1];
		i++;
		if (env[i])
			my_env->next = (t_env *)malloc(sizeof(t_env)); // NULL GUARD
		my_env = my_env->next;
		free(str);
	}
}

void	init_shell(t_shell *my_shell, char **env)
{
	my_shell->env = (t_env *)malloc(sizeof(t_env)); // NULL GUARD
	ft_memset(my_shell->env, 0, sizeof(t_env));
	init_env(my_shell->env, env);
	init_signal();
}
