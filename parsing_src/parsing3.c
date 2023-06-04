/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:32:23 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/03 18:05:30 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_heredoc_value(t_token *token)
{
	int	i;

	if (token == NULL)
		return ;
	if (token->type != WORD)
		return ;
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
			delete_single_quote(token);
		else if (token->value[i] == '\"')
			delete_double_quote_heredoc(token);
		i++;
	}
	token->type = HEREDOC;
}


void	check_token(t_token *token, t_shell *ms)
{
	t_token	*start;
	int		i;

	start = token;
	while (start)
	{
		if (token->type == REDIRECTION && ft_strcmp("<<", token->value) == 0)
			check_heredoc_value(start->next);
		start = start->next;
	}

	start = token;
	while (start)
	{
		i = 0;
		while (start->value[i])
		{
			if (start->value[i] == '\'')
			{
				i += delete_single_quote(start);
				continue ;
			}
			else if (start->value[i] == '\"')
			{
				i += delete_double_quote(start, ms);
				continue ;
			}
			else if (start->value[i] == '$' && start->type != HEREDOC)
			{
				i += replace_env(start, ms);
				if (start->type == -1 && ft_strcmp(start->value, "") == 0)
				{
					free(start->value);
					start->value = NULL;
					break;
				}
				if (start->type == -1)
					start->type = WORD;
				continue ;
			}
			i++;
		}
		start = start->next;
	}
}
