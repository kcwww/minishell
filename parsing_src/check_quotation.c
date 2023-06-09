/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:48:15 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 20:11:08 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

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
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i = check_double(str, i + 1, '\"');
			if (i == -1)
				break ;
		}
		if (str[i] == '\'')
		{
			i = check_double(str, i + 1, '\'');
			if (i == -1)
				break ;
		}
		i++;
	}
	if (i == -1)
	{
		error_str();
		return (0);
	}
	return (1);
}
