/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:33:13 by dkham             #+#    #+#             */
/*   Updated: 2023/06/08 21:00:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(t_shell *my_shell, t_pipes *head)
{
	int		i;
	char	**word;

	word = head->simple_cmd->word;
	i = 1;
	while (word[i])
	{
		remove_env_node(word[i], &my_shell->env);
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
