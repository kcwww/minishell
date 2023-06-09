/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:34:54 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 23:21:33 by chanwoki         ###   ########.fr       */
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
		g_exit_status = 130;
	}
	else if (signo == SIGQUIT)
		return ;
}

void	sig_herdoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		close(0);
	}
}

void	check_signum(int signo)
{
	if (signo == SIGINT)
		printf("\n");
	else if (signo == SIGQUIT)
		printf("Quit: 3\n");
}

void	init_env(t_env *my_env, char **env)
{
	int		i;
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
		{
			my_env->next = (t_env *)malloc(sizeof(t_env));
			if (my_env->next == NULL)
				return ;
		}
		my_env = my_env->next;
		free(str);
	}
}

void	init_shell(t_shell *my_shell, char **env)
{
	g_exit_status = 0;
	my_shell->env = (t_env *)malloc(sizeof(t_env));
	if (my_shell->env == NULL)
		return ;
	ft_memset(my_shell->env, 0, sizeof(t_env));
	init_env(my_shell->env, env);
	sigemptyset(&my_shell->sa_sigint.sa_mask);
	sigemptyset(&my_shell->sa_sigquit.sa_mask);
	init_signal(my_shell);
}
