/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:23:09 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/03 13:52:58 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delete_single_quote(t_token *token)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	start = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			start = i;
			i++;
			tmp = ft_substr(token->value, 0, start);
			break ;
		}
		i++;
	}

	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			tmp3  = ft_substr(token->value, start + 1, i - start - 1);
			tmp2 = ft_strjoin(tmp, tmp3);
			free(tmp);
			free(tmp3);
			len = i - start - 1;
			start = i + 1;
			break ;
		}
		i++;
	}
	while (token->value[i])
		i++;
	tmp3 = ft_substr(token->value, start, i);
	tmp = ft_strjoin(tmp2, tmp3);
	free(token->value);
	free(tmp3);
	free(tmp2);
	token->value = tmp;
	return (len);
}
