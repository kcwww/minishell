/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/05/07 12:21:40 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// echo $a option 구현해야 함

void	echo(t_execute *execute)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = handle_n_flag(execute->args, &i);
	print_args(execute, i, n_flag);
}

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

void	print_args(t_execute *execute, int i, int n_flag)
{
	char	*env_var_val;

	while (execute->args[i])
	{
		env_var_val = get_env_var_value(execute, execute->args[i]);
		if (env_var_val)
			ft_putstr_fd(env_var_val, execute->fd_out);
		else
			ft_putstr_fd(execute->args[i], execute->fd_out);
		if (execute->args[i + 1])
			ft_putstr_fd(" ", execute->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", execute->fd_out);
}

char	*get_env_var_value(t_execute *execute, const char *str)
{
	char	*value;
	char	*key;
	t_env	*found_env;

	if (str[0] == '$')
	{
		key = ft_strdup(str + 1);
		found_env = find_env_node(execute->env, key);
		free(key);
		if (found_env && found_env->value)
			value = found_env->value;
		else
			value = NULL;
		return (value);
	}
	return (NULL);
}
