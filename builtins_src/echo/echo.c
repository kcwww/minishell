/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/06/07 20:19:25 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(t_shell *my_shell, t_pipes *head)
{
	int		i;
	int		n_flag;
	char	**word;

	word = head->simple_cmd->word;
	i = 1;
	n_flag = handle_n_flag(word, &i);
	print_word(my_shell, head, i, n_flag);
}

int	handle_n_flag(char **word, int *i)
{
	int	n_flag;

	n_flag = 0;
	while (word[*i] && ft_strncmp(word[*i], "-n", 2) == 0)
	{
		if (only_n_after_dash(word[*i]))
		{
			n_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (n_flag);
}

int	only_n_after_dash(const char *str)
{
	int	j;

	j = 2;
	while (str[j])
	{
		if (str[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	print_word(t_shell *my_shell, t_pipes *head, int i, int n_flag)
{
	char	**word;

	word = head->simple_cmd->word;
	while (word[i])
	{
		ft_putstr_fd(word[i], my_shell->fd_out);
		if (word[i + 1])
			ft_putstr_fd(" ", my_shell->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", my_shell->fd_out);
}
