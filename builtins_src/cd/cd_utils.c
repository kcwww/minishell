/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:06:13 by dkham             #+#    #+#             */
/*   Updated: 2023/06/09 16:36:23 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*found_env;
	size_t	key_len;
	char	*key_val_pair;
	t_env	*new_node;

	found_env = find_env_node(env, key);
	if (found_env)
	{
		free(found_env->value);
		found_env->value = ft_strdup(value);
	}
	else
	{
		key_len = ft_strlen(key);
		key_val_pair = malloc((key_len + ft_strlen(value) + 2) * sizeof(char));
		if (!key_val_pair)
			return ;
		ft_strlcpy(key_val_pair, key, key_len + 1);
		key_val_pair[key_len] = '=';
		ft_strlcpy(key_val_pair + key_len + 1, value, ft_strlen(value) + 1);
		new_node = create_new_env_node(key_val_pair);
		if (new_node)
			add_env_node(env, new_node);
		free(key_val_pair);
	}
}

t_env	*create_new_env_node(char *key_value_pair)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(key_value_pair, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		new_node->key = ft_strdup(key_value_pair);
		new_node->value = ft_strdup(equal_sign + 1);
		*equal_sign = '=';
	}
	else
	{
		new_node->key = ft_strdup(key_value_pair);
		new_node->value = ft_strdup("");
	}
	new_node->next = NULL;
	return (new_node);
}
