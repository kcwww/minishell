/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:34:00 by dkham             #+#    #+#             */
/*   Updated: 2023/05/05 17:40:20 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// replicate export command(with no options) in bash
// it should be able to add new variables to the environment

void	process_argument(char *arg, t_execute *execute)
{
	t_env	*new_node;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (is_valid_identifier(arg))
	{
		if (equal_sign != NULL)
		{
			new_node = create_new_env_node(arg);
			if (new_node)
				add_env_node(execute->env, new_node);
		}
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 1);
		ft_putstr_fd(arg, 1);
		ft_putendl_fd("' is not a valid identifier", 1);
	}
}

void	export(char **args, t_execute *execute)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		print_env_list(execute->env);
		return ;
	}
	while (args[i])
	{
		process_argument(args[i], execute);
		i++;
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

void	add_env_node(t_env *env, t_env *new_node) 
{
	t_env	*tmp;
	size_t	new_node_key_len;

	tmp = env;
	new_node_key_len = ft_strlen(new_node->key) + 1;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, new_node->key, new_node_key_len) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_node->value);
			free_env_node(new_node);
			return ;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new_node;
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
