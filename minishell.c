/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:57:40 by dkham             #+#    #+#             */
/*   Updated: 2023/05/28 15:45:59 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
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
		if (ft_strcmp("", get_line) == 0)
		{
			free(get_line);
			continue ;
		}
		if (get_line == NULL)
		{
			printf("exit\n");
			free_env(my_shell.env);
			return (0);
		}
		if (check_quotation(get_line) && check_whitespace(get_line))
		{
			parsing_start(get_line, &my_shell);
			if (my_shell.error == 1)
				printf("no execute\n");
			else
				execute(&my_shell, env);
			free_all(&my_shell);
		}
		add_history(get_line);
		free(get_line);
	}
	return (0);
}
