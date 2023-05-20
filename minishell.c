/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:30:44 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/20 14:04:06 by chanwoki         ###   ########.fr       */
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
		add_history(get_line);
		if (check_quotation(get_line))
		{
			// if (ft_strcmp("None", find_value(get_line, &my_shell)) != 0) //delete
			// 	printf("%s\n", find_value(get_line, &my_shell)); //delete
			parsing_start(get_line, &my_shell);
		}
		if (my_shell.error == 1)
			printf("no execute\n");
			//execute();
		free(get_line);
		free_all(&my_shell);
	}
	return (0);
}
