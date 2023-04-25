/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:40:19 by chanwoki          #+#    #+#             */
/*   Updated: 2022/11/17 22:02:47 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*temp;

	i = 1;
	temp = lst;
	if (lst == 0)
		return (0);
	while (temp->next)
	{
		lst = lst->next;
		temp = lst;
		i++;
	}
	return (i);
}
