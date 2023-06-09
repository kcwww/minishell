/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:42:54 by dkham             #+#    #+#             */
/*   Updated: 2023/06/09 17:31:43 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_exit(t_shell *my_shell, t_pipes *head, int i)
{
	char	*error_message;

	error_message = validate_exit_word(head);
	if (error_message)
	{
		ft_putstr_fd("exit\n", my_shell->fd_out);
		ft_putstr_fd("minishell: exit: ", my_shell->fd_out);
		if (g_exit_status != 1)
		{
			ft_putstr_fd(head->simple_cmd->word[1], my_shell->fd_out);
			ft_putstr_fd(": ", my_shell->fd_out);
		}
		ft_putendl_fd(error_message, my_shell->fd_out);
	}
	else if (head->next == NULL && i == 0)
		ft_putstr_fd("exit\n", my_shell->fd_out);
	if (ft_strcmp(error_message, "too many arguments") != 0)
	{
		free_env(my_shell->env);
		free_all(my_shell);
		free(my_shell->line);
		exit(g_exit_status);
	}
}

char	*validate_exit_word(t_pipes *head)
{
	char	**word;

	word = head->simple_cmd->word;
	if (word[1])
	{
		if (!is_numeric(word[1]))
			return ("numeric argument required");
		if (is_too_many_args(word))
			return ("too many arguments");
		g_exit_status = ft_atoi(word[1]);
	}
	else
		g_exit_status = 0;
	return (NULL);
}

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
	{
		g_exit_status = 2;
		return (0);
	}
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			g_exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_too_many_args(char **word)
{
	if (word[2])
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
