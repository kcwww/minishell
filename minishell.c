/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:45:05 by dkham             #+#    #+#             */
/*   Updated: 2023/05/31 19:31:04 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_shell	my_shell;

	atexit(check_leaks);
	if (argc != 1)
		return (0);
	(void)argv;
	init_shell(&my_shell, env);
	while (1)
	{
		my_shell.line = readline("minishell $ ");
		if (ft_strcmp("", my_shell.line) == 0)
		{
			free(my_shell.line);
			continue ;
		}
		if (my_shell.line == NULL)
		{
			printf("exit\n");
			free_env(my_shell.env);
			return (0);
		}
		if (check_quotation(my_shell.line) && check_whitespace(my_shell.line))
		{
			parsing_start(my_shell.line, &my_shell);
			if (my_shell.error == 1)
				printf("no execute\n");
			else
				execute(&my_shell, env);
			free_all(&my_shell);
		}
		add_history(my_shell.line);
		free(my_shell.line);
	}
	return (0);
}
