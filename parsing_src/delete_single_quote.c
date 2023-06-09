/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:23:09 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 20:38:54 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_without_single_quote(t_tmp *str, t_token *token, int *start, int i)
{
	int	len;

	str->tmp3 = ft_substr(token->value, (*start) + 1, i - (*start) - 1);
	str->tmp2 = ft_strjoin(str->tmp, str->tmp3);
	free_three(str->tmp, str->tmp3, NULL);
	len = i - (*start) - 1;
	*start = i + 1;
	return (len);
}

int	delete_single_quote(t_token *token, int idx)
{
	int		i;
	int		start;
	int		len;
	t_tmp	str;

	i = idx + 1;
	start = idx;
	str.tmp = ft_substr(token->value, 0, start);
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			len = create_without_single_quote(&str, token, &start, i);
			break ;
		}
		i++;
	}
	while (token->value[i])
		i++;
	str.tmp3 = ft_substr(token->value, start, i - start);
	str.tmp = ft_strjoin(str.tmp2, str.tmp3);
	free_three(str.tmp2, str.tmp3, token->value);
	token->value = str.tmp;
	return (len);
}
