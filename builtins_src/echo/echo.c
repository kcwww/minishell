/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/05/04 19:38:39 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// echo $a option 구현해야 함

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

char	*expand_env_var(const char *str)
{
	char	*value;

	if (str[0] == '$')
	{
		value = getenv(str + 1);
		if (value)
			return (value);
	}
	return (NULL);
}

// void	echo(char **args, t_execute *execute)
// {
// 	int		i;
// 	int		n_flag;
// 	char	*expanded;

// 	i = 1;
// 	n_flag = 0;
// 	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
// 	{
// 		if (only_n_after_dash(args[i]))
// 		{
// 			n_flag = 1;
// 			i++;
// 		}
// 		else
// 			break ;
// 	}
// 	while (args[i])
// 	{
// 		expanded = expand_env_var(args[i]);
// 		if (expanded)
// 			ft_putstr_fd(expanded, execute->fd_out);
// 		else
// 			ft_putstr_fd(args[i], execute->fd_out);
// 		if (args[i + 1])
// 			ft_putstr_fd(" ", execute->fd_out);
// 		i++;
// 	}
// 	if (n_flag == 0)
// 		ft_putstr_fd("\n", execute->fd_out);
// }

int	handle_n_flag(char **args, int *i)
{
	int	n_flag;

	n_flag = 0;
	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		if (only_n_after_dash(args[*i]))
		{
			n_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (n_flag);
}

void	print_args(char **args, int i, int n_flag, t_execute *execute)
{
	char	*expanded;

	while (args[i])
	{
		expanded = expand_env_var(args[i]);
		if (expanded)
			ft_putstr_fd(expanded, execute->fd_out);
		else
			ft_putstr_fd(args[i], execute->fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", execute->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", execute->fd_out);
}

void	echo(char **args, t_execute *execute)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = handle_n_flag(args, &i);
	print_args(args, i, n_flag, execute);
}
