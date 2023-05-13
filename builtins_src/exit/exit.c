/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:42:54 by dkham             #+#    #+#             */
/*   Updated: 2023/05/13 13:08:06 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_exit(t_shell *myshell)
{
	int		exit_code;
	char	*error_message;
	char	**word;

	word = myshell->head->simple_cmd->word;
	error_message = validate_exit_word(myshell, &exit_code);
	if (error_message)
	{
		ft_putstr_fd("exit\n", myshell->fd_out);
		ft_putstr_fd("minishell: exit: ", myshell->fd_out);
		ft_putstr_fd(error_message, myshell->fd_out);
		ft_putstr_fd("\n", myshell->fd_out);
	}
	else
		exit(exit_code);
}

char	*validate_exit_word(t_shell *myshell, int *exit_code)
{
	int		i;
	char	**word;

	word = myshell->head->simple_cmd->word;
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
