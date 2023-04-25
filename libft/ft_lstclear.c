/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:05:20 by chanwoki          #+#    #+#             */
/*   Updated: 2023/01/01 18:59:32 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*start;

	if (lst == 0 || *lst == 0)
		return ;
	start = *lst;
	while (start)
	{
		(*lst) = (*lst)->next;
		free(start);
		start = *lst;
	}
}
