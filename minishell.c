/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:19:18 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/13 16:07:02 by dkham            ###   ########.fr       */
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

	//atexit(check_leaks);
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
			return (0);
		}
		add_history(get_line);
		if (check_quotation(get_line))
		{
			// printf("%s\n", get_line); // delete
			// if (ft_strcmp("None", find_value(get_line, my_shell.env)) != 0) //delete
			// printf("%s\n", find_value(get_line, my_shell.env)); //delete
			parsing_start(get_line, &my_shell);
		}
		execute(&my_shell);
		free(get_line);
		free_all(&my_shell);
	}
	return (0);
}
