/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:32:23 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 21:45:48 by chanwoki         ###   ########.fr       */
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
			delete_single_quote(token, i);
		else if (token->value[i] == '\"')
			delete_double_quote_heredoc(token, i);
		i++;
	}
	token->type = HEREDOC;
}

int	check_env_type(t_token *start)
{
	if (start->type == -1 && ft_strcmp(start->value, "") == 0)
	{
		free(start->value);
		start->value = NULL;
		return (1);
	}
	if (start->type == -1)
		start->type = WORD;
	return (0);
}

void	delete_and_replace(t_token *start, t_shell *ms)
{
	int	i;

	i = 0;
	while (start->value[i])
	{
		if (start->value[i] == '\'')
		{
			i += delete_single_quote(start, i);
			continue ;
		}
		else if (start->value[i] == '\"')
		{
			i += delete_double_quote(start, ms, i);
			continue ;
		}
		else if (start->value[i] == '$' && start->type != HEREDOC)
		{
			i += replace_env(start, ms, i);
			if (check_env_type(start))
				break ;
			continue ;
		}
		i++;
	}
}

void	check_token(t_token *token, t_shell *ms)
{
	t_token	*start;

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
		delete_and_replace(start, ms);
		start = start->next;
	}
}
