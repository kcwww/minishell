/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:57:04 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 22:59:24 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_without_double_quote(t_tmp *str, t_token *token, int *start, int i)
{
	int	len;

	str->tmp = ft_substr(token->value, 0, *start);
	str->tmp3 = ft_substr(token->value, *start + 1, i - (*start) - 1);
	str->tmp2 = ft_strjoin(str->tmp, str->tmp3);
	free_three(str->tmp3, str->tmp, NULL);
	len = i - (*start) - 1;
	*start = i + 1;
	return (len);
}

void	deleted_value(t_tmp *str, t_token *token, int start, int i)
{
	str->tmp3 = ft_substr(token->value, start, i);
	str->tmp = ft_strjoin(str->tmp2, str->tmp3);
	free_three(str->tmp3, str->tmp2, token->value);
	token->value = str->tmp;
}

int	delete_double_quote(t_token *token, t_shell *ms, int idx)
{
	int		i;
	int		start;
	int		len;
	t_tmp	str;

	i = idx + 1;
	start = idx;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			i += replace_env_quote(token, ms, i);
			continue ;
		}
		if (token->value[i] == '\"')
		{
			len = create_without_double_quote(&str, token, &start, i);
			break ;
		}
		i++;
	}
	while (token->value[i])
		i++;
	deleted_value(&str, token, start, i);
	return (len);
}
