/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/05/02 21:04:33 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv)
{
	char	*get_line;

	//atexit(check_leaks);
	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		get_line = readline("minishell $ ");
		if (get_line == NULL)
		{
			error_str();
			return (0);
		}
		// split line
		char **args = ft_split(get_line, ' ');
		// set struct
		t_execute execute;
		execute.fd_out = 1;
		// run builtin function
		builtin(args, &execute);
		// add_history
		add_history(get_line);
		//ft_printf("%s\n", get_line);
		free(get_line);
	}
	return (0);
}
