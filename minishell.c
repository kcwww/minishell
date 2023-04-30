/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/04/30 19:24:28 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv)
{
	// char	*get_line;

	// atexit(check_leaks);
	// if (argc != 1)
	// 	return (0);
	// (void)argv;
	// while (1)
	// {
	// 	get_line = readline("minishell $ ");
	// 	if (get_line == NULL)
	// 	{
	// 		error_str();
	// 		return (0);
	// 	}
	// 	ft_printf("%s\n", get_line);
	// 	free(get_line);
	// }


	// prevent unused parameter argc, argv
	(void)argc;
	(void)argv;
	// 1. pwd
	// pwd();
	
	// 2. echo
	// char	*args[] = {"echo", "-n", "hello", "world", NULL};
	// echo(args);

	// 3. exit
	// exit(0);
}
