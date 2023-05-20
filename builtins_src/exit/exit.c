/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:42:54 by dkham             #+#    #+#             */
/*   Updated: 2023/05/20 17:54:52 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_exit(t_shell *my_shell)
{
	int		exit_code;
	char	*error_message;

	error_message = validate_exit_word(my_shell, &exit_code);
	if (error_message)
	{
		ft_putstr_fd("exit\n", my_shell->fd_out);
		ft_putstr_fd("minishell: exit: ", my_shell->fd_out);
		ft_putstr_fd(error_message, my_shell->fd_out);
		ft_putstr_fd("\n", my_shell->fd_out);
	}
	else
		exit(exit_code);
}

char	*validate_exit_word(t_shell *my_shell, int *exit_code)
{
	int		i;
	char	**word;

	word = my_shell->head->simple_cmd->word;
	i = 0;
	if (word[1])
	{
		while (word[1][i])
		{
			if (ft_isdigit(word[1][i]) == 0)
			{
				*exit_code = 255;
				return ("numeric argument required");
			}
			i++;
		}
		if (word[2])
		{
			*exit_code = 1;
			return ("too many arguments");
		}
		else
			*exit_code = ft_atoi(word[1]);
	}
	else
		*exit_code = 0;
	return (NULL);
}
