/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:35:30 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/28 16:24:37 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(char *key, t_shell *ms)
{
	t_env	*lst;

	lst = ms->env;
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}
