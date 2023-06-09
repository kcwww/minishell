/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_double_quote_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:51:23 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 21:45:03 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_three(char *tmp, char *tmp2, char *tmp3)
{
	if (tmp != NULL)
		free(tmp);
	if (tmp2 != NULL)
		free(tmp2);
	if (tmp3 != NULL)
		free(tmp3);
}

void	delete_double_quote_heredoc(t_token *token, int idx)
{
	int		i;
	int		start;
	t_tmp	str;

	i = idx + 1;
	start = idx;
	str.tmp = ft_substr(token->value, 0, start);
	while (token->value[i])
	{
		if (token->value[i] == '\"')
		{
			str.tmp3 = ft_substr(token->value, start + 1, i - start - 1);
			str.tmp2 = ft_strjoin(str.tmp, str.tmp3);
			free_three(str.tmp3, str.tmp, NULL);
			start = i + 1;
			break ;
		}
		i++;
	}
	while (token->value[i])
		i++;
	str.tmp3 = ft_substr(token->value, start, i);
	str.tmp = ft_strjoin(str.tmp2, str.tmp3);
	free_three(str.tmp3, str.tmp2, token->value);
	token->value = str.tmp;
}
