/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_double_quote_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:51:23 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 16:48:33 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_double_quote_heredoc(t_token *token, int idx)
{
	int		i;
	int		start;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = idx + 1;
	start = idx;
	tmp = ft_substr(token->value, 0, start);

	while (token->value[i])
	{
		if (token->value[i] == '\"')
		{
			tmp3  = ft_substr(token->value, start + 1, i - start - 1);
			tmp2 = ft_strjoin(tmp, tmp3);
			free(tmp);
			free(tmp3);
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
}
