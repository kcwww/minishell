/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:14:12 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/13 13:57:55 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(char *key, t_env *env)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return ("None");
}
