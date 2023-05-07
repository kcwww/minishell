/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:33:13 by dkham             #+#    #+#             */
/*   Updated: 2023/05/07 12:50:01 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(t_execute *execute)
{
	int		i;

	i = 1;
	while (execute->args[i])
	{
		if (is_valid_identifier(execute->args[i]))
			remove_env_node(execute->args[i], &execute->env);
		else
		{
			ft_putstr_fd("minishell: unset: '", 1);
			ft_putstr_fd(execute->args[i], 1);
			ft_putendl_fd("' is not a valid identifier", 1);
		}
		i++;
	}
}

void	remove_env_node(char *key, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	size_t	key_len;

	tmp = *env;
	prev = NULL;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, key_len) == 0
			&& tmp->key[key_len] == '\0')
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free_env_node(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
