/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:51:38 by dkham             #+#    #+#             */
/*   Updated: 2023/05/27 13:42:23 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_argument_with_equals(char *arg, t_shell *my_shell)
{
	t_env	*new_node;

	new_node = create_new_env_node(arg);
	if (new_node)
		add_env_node(my_shell->env, new_node);
}

void	handle_argument_without_equals(char *arg, t_shell *my_shell)
{
	t_env	*found_env;
	t_env	*new_node;

	found_env = find_env_node(my_shell->env, arg);
	if (!found_env)
	{
		new_node = create_new_env_node(arg);
		if (new_node)
			add_env_node(my_shell->env, new_node);
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

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}
