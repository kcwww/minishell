/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:34:00 by dkham             #+#    #+#             */
/*   Updated: 2023/05/05 18:45:13 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// replicate export command(with no options) in bash
// it should be able to add new variables to the environment

void	export(char **args, t_execute *execute)
{
	int		i;
	t_env	*sorted_env;

	i = 1;
	if (args[1] == NULL)
	{
		sorted_env = sort_env_list(execute->env);
		print_env_list(sorted_env);
		return ;
	}
	while (args[i])
	{
		process_argument(args[i], execute);
		i++;
	}
}

t_env	*sort_env_list(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		swapped;
	size_t	max_length;

	if (!env)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp1 = env;
		while (tmp1->next != NULL)
		{
			tmp2 = tmp1->next;
			if (ft_strlen(tmp1->key) > ft_strlen(tmp2->key))
				max_length = ft_strlen(tmp1->key);
			else
				max_length = ft_strlen(tmp2->key);
			if (ft_strncmp(tmp1->key, tmp2->key, max_length) > 0)
			{
				swap_env_nodes(tmp1, tmp2);
				swapped = 1;
			}
			tmp1 = tmp1->next;
		}
	}
	return (env);
}

void	swap_env_nodes(t_env *node1, t_env *node2)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = node1->key;
	temp_value = node1->value;
	node1->key = node2->key;
	node1->value = node2->value;
	node2->key = temp_key;
	node2->value = temp_value;
}

void	handle_argument_with_equals(char *arg, t_execute *execute)
{
	t_env	*new_node;

	new_node = create_new_env_node(arg);
	if (new_node)
		add_env_node(execute->env, new_node);
}

void	handle_argument_without_equals(char *arg, t_execute *execute)
{
	t_env	*found_env;
	t_env	*new_node;

	found_env = find_env_node(execute->env, arg);
	if (!found_env)
	{
		new_node = create_new_env_node(arg);
		if (new_node)
			add_env_node(execute->env, new_node);
	}
}

void	process_argument(char *arg, t_execute *execute)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (is_valid_identifier(arg))
	{
		if (equal_sign != NULL)
			handle_argument_with_equals(arg, execute);
		else
			handle_argument_without_equals(arg, execute);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", 1);
		ft_putstr_fd(arg, 1);
		ft_putendl_fd("' is not a valid identifier", 1);
	}
}

t_env	*find_env_node(t_env *env, char *key)
{
	t_env	*tmp;
	size_t	key_len;

	tmp = env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, key_len) == 0
			&& tmp->key[key_len] == '\0')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
