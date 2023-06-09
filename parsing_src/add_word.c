/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:51:04 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 19:51:54 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	add_word_pipe(t_token *token, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (process_special_char(token, '|', 2));
	return (i);
}

int	add_word_greater(t_token *token, char *str, int i)
{
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
		{
			return (process_special_char(token, '>', 3));
		}
		else
		{
			i--;
			return (process_special_char(token, '>', 2));
		}
	}
	return (i);
}

int	add_word_less(t_token *token, char *str, int i)
{
	if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
		{
			return (process_special_char(token, '<', 3));
		}
		else
		{
			i--;
			return (process_special_char(token, '<', 2));
		}
	}
	return (i);
}

int	add_word(t_token *token, char *str)
{
	int	i;

	i = add_word_pipe(token, str);
	if (i != 0)
		return (i);
	i = add_word_greater(token, str, i);
	if (i != 0)
		return (i);
	i = add_word_less(token, str, i);
	if (i != 0)
		return (i);
	return (process_string(token, str));
}
