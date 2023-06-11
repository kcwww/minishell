/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:29:54 by dkham             #+#    #+#             */
/*   Updated: 2023/06/10 00:52:43 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_and_exe(t_shell *my_shell, char **env)
{
	if (check_quotation(my_shell->line) && check_whitespace(my_shell->line))
	{
		parsing_start(my_shell->line, my_shell);
		if (my_shell->error != 1)
			execute(my_shell, env);
		free_all(my_shell);
	}
}

static void	wrong_argc(void)
{
	printf("Wrong ARGCS Error\n");
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	my_shell;

	if (argc != 1)
		wrong_argc();
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
		parse_and_exe(&my_shell, env);
		add_history(my_shell.line);
		free(my_shell.line);
	}
	return (0);
}
