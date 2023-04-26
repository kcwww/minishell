/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/04/26 11:20:24 by kcw              ###   ########.fr       */
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
		get_line = get_next_line(0);
		if (get_line == NULL)
		{
			ft_printf("exit\n");
			return (0);
		}
		ft_printf("%s", get_line);
		free(get_line);
	}
}
