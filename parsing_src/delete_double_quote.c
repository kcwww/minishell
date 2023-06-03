/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:57:04 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/03 17:48:05 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int delete_double_quote(t_token *token, t_shell *ms)
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
		if (token->value[i] == '\"')
		{
			start = i;
			i++;
			break ;
		}
		i++;
	}

	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			i += replace_env_quote(token, ms, i);

		}
		if (token->value[i] == '\"')
		{
			tmp = ft_substr(token->value, 0, start);
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
