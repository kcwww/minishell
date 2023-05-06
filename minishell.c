/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/05/06 13:26:04 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

void	ft_shellclear(t_env **env)
{
	t_env	*start;

	if (env == 0 || *env == 0)
		return ;
	start = *env;
	while (start)
	{
		(*env) = (*env)->next;
		free(start->var);
		free(start->param);
		free(start->value);
		free(start);
		start = *env;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*get_line;
	t_shell	my_shell;

	atexit(check_leaks);
	if (argc != 1)
		return (0);
	(void)argv;
	init_shell(&my_shell, env);
	while (1)
	{
		get_line = readline("minishell $ ");
		if (get_line == NULL)
		{
			printf("exit\n");
			ft_shellclear(&my_shell.env);
			return (0);
		}
		add_history(get_line);
		printf("%s\n", find_value(get_line, my_shell.env));
		ft_printf("%s\n", get_line);
		free(get_line);
	}
}
