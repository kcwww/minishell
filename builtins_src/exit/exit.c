/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:42:54 by dkham             #+#    #+#             */
/*   Updated: 2023/06/07 20:47:46 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_exit(t_shell *my_shell)
{
	char	*error_message;

	error_message = validate_exit_word(my_shell, &g_exit_status);
	if (error_message)
	{
		ft_putstr_fd("exit\n", my_shell->fd_out);
		ft_putstr_fd("minishell: exit: ", my_shell->fd_out);
		if (g_exit_status != 1)
		{
			ft_putstr_fd(my_shell->head->simple_cmd->word[1], my_shell->fd_out);
			ft_putstr_fd(": ", my_shell->fd_out);
		}
		ft_putendl_fd(error_message, my_shell->fd_out);
	}
	free_env(my_shell->env);
	free_all(my_shell);
	free(my_shell->line);
	exit(g_exit_status);
}

int	is_numeric(char *arg, int *g_exit_status)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
	{
		*g_exit_status = 2;
		return (0);
	}
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			*g_exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_too_many_args(char **word, int *g_exit_status)
{
	if (word[2])
	{
		*g_exit_status = 1;
		return (1);
	}
	return (0);
}

char	*validate_exit_word(t_shell *my_shell, int *g_exit_status)
{
	char	**word;

	word = my_shell->head->simple_cmd->word;
	if (word[1])
	{
		if (!is_numeric(word[1], g_exit_status))
			return ("numeric argument required");
		if (is_too_many_args(word, g_exit_status))
			return ("too many arguments");
		*g_exit_status = ft_atoi(word[1]);
	}
	else
		*g_exit_status = 0;
	return (NULL);
}
