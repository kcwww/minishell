/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:48:15 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/14 12:20:03 by kcw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_double(char *str, int i, char mark)
{
	while (str[i])
	{
		if (str[i] == mark)
			return (i);
		i++;
	}
	return (-1);
}

int	check_quotation(char *str)
{
	int		i;
	int		q;

	i = 0;
	q = 0;

	while (str[i])
	{
		if (str[i] == '\"')
		{
			q = check_double(str, i + 1, '\"');
			if (q == -1)
			{
				error_str();
				return (0);
			}
			else
				i = q;
		}
		if (str[i] == '\'')
		{
			q = check_double(str, i + 1, '\'');
			if (q == -1)
			{
				error_str();
				return (0);
			}
			else
				i = q;
		}
		i++;
	}
	return (1);
}
