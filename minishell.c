/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/04/28 14:07:55 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv)
{
	char	*get_line;

	atexit(check_leaks);
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
		ft_printf("%s\n", get_line);
		free(get_line);
	}
}
