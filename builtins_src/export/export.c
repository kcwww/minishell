/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:34:00 by dkham             #+#    #+#             */
/*   Updated: 2023/06/04 16:24:32 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export(t_shell *my_shell)
{
	int		i;
	t_env	*sorted_env;
	char	**word;

	word = my_shell->head->simple_cmd->word;
	i = 1;
	if (word[1] == NULL)
	{
		sorted_env = sort_env_list(my_shell->env);
		print_env_list(sorted_env, my_shell);
		return ;
	}
	while (word[i])
	{
		process_argument(word[i], my_shell);
		i++;
	}
}

void	print_env_list(t_env *env, t_shell *my_shell)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", my_shell->fd_out);
		ft_putstr_fd(tmp->key, my_shell->fd_out);
		if (tmp->value && tmp->value[0] != '\0')
		{
			ft_putstr_fd("=\"", my_shell->fd_out);
			ft_putstr_fd(tmp->value, my_shell->fd_out);
			ft_putendl_fd("\"", my_shell->fd_out);
		}
		else
		{
			ft_putendl_fd("", my_shell->fd_out);
		}
		tmp = tmp->next;
	}
}

void	process_argument(char *arg, t_shell *my_shell)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (is_valid_identifier(arg))
	{
		if (equal_sign != NULL)
			handle_argument_with_equals(arg, my_shell);
		else
			handle_argument_without_equals(arg, my_shell);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", my_shell->fd_out);
		ft_putstr_fd(arg, my_shell->fd_out);
		ft_putendl_fd("' not a valid identifier", my_shell->fd_out);
		g_exit_status = 1;
	}
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i])) // if 
	{
		i++;
		while (arg[i] != '\0' && arg[i] != '=')
		{
			if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
