/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:47:25 by dkham             #+#    #+#             */
/*   Updated: 2023/05/06 12:48:16 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*sort_env_list(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		swapped;

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
			if (cmp_env_nodes(tmp1, tmp2))
			{
				swap_env_nodes(tmp1, tmp2);
				swapped = 1;
			}
			tmp1 = tmp1->next;
		}
	}
	return (env);
}

int	cmp_env_nodes(t_env *tmp1, t_env *tmp2)
{
	size_t	max_length;

	if (ft_strlen(tmp1->key) > ft_strlen(tmp2->key))
		max_length = ft_strlen(tmp1->key);
	else
		max_length = ft_strlen(tmp2->key);
	if (ft_strncmp(tmp1->key, tmp2->key, max_length) > 0)
		return (1);
	else
		return (0);
}

void	swap_env_nodes(t_env *tmp1, t_env *tmp2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = tmp1->key;
	tmp_value = tmp1->value;
	tmp1->key = tmp2->key;
	tmp1->value = tmp2->value;
	tmp2->key = tmp_key;
	tmp2->value = tmp_value;
}

