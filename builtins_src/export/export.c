/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:34:00 by dkham             #+#    #+#             */
/*   Updated: 2023/05/13 13:08:29 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export(t_shell *myshell)
{
	int		i;
	t_env	*sorted_env;
	char	**word;

	word = myshell->head->simple_cmd->word;
	i = 1;
	if (word[1] == NULL)
	{
		sorted_env = sort_env_list(myshell->env);
		print_env_list(sorted_env);
		return ;
	}
	while (word[i])
	{
		process_argument(word[i], myshell);
		i++;
	}
}

void	print_env_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value && tmp->value[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
		{
			ft_putendl_fd("", 1);
		}
		tmp = tmp->next;
	}
}

void	process_argument(char *arg, t_shell *myshell)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (is_valid_identifier(arg))
	{
		if (equal_sign != NULL)
			handle_argument_with_equals(arg, myshell);
		else
			handle_argument_without_equals(arg, myshell);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", 1);
		ft_putstr_fd(arg, 1);
		ft_putendl_fd("' is not a valid identifier", 1);
	}
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i]))
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
