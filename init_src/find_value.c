/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:14:12 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/14 12:48:07 by kcw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(char *key, t_shell *ms)
{
	t_env	*lst;

	lst = ms->env;
	while (lst)
	{
		if (ft_strcmp(key, lst->param) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return ("None");
}
