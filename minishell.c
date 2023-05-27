/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:57:40 by dkham             #+#    #+#             */
/*   Updated: 2023/05/27 13:32:59 by kcw              ###   ########.fr       */
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
		if (get_line == NULL)
		{
			printf("exit\n");
			free_env(my_shell.env);
			return (0);
		}


		if (check_quotation(get_line))
		{
			parsing_start(get_line, &my_shell);
			if (my_shell.error == 1)
				printf("no execute\n");
			else
				execute(&my_shell, env);
			if (ft_strcmp("", find_value(get_line, &my_shell)) != 0)
				printf("%s\n", find_value(get_line, &my_shell));
			free_all(&my_shell);
		}
		add_history(get_line);
		free(get_line);
	}
	return (0);
}
