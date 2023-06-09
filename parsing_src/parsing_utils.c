/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:53:45 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 19:54:31 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_special_char(t_token *token, char ch, int size)
{
	int		type;
	char	*value;

	value = (char *)malloc(sizeof(char) * size);
	if (value == 0)
		return (-1);
	value[0] = ch;
	if (size == 3)
		value[1] = ch;
	value[size - 1] = '\0';
	if (ch == '|')
	{
		type = PIPE;
	}
	else
	{
		type = REDIRECTION;
	}
	token->value = value;
	token->type = type;
	return (size - 1);
}

int	process_string(t_token *token, char *str)
{
	int		i;
	char	ch;
	char	*value;

	i = 0;
	while (str[i])
	{
		ch = str[i];
		if (ch == '\"' || ch == '\'')
		{
			i++;
			while (str[i] != ch)
				i++;
		}
		if (str[i] == ' ' || str[i] == '|' || str[i] == '>' || str[i] == '<')
			break ;
		i++;
	}
	value = (char *)malloc(sizeof(char) * (i + 1));
	if (value == 0)
		return (-1);
	ft_strlcpy(value, str, i + 1);
	token->value = value;
	token->type = WORD;
	return (i);
}

t_token	*create_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == 0)
		return (NULL);
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}

int	process_new_string(t_token *token, char *str, int i)
{
	char	*new_str;

	new_str = ft_substr(str, i, ft_strlen(str) - i);
	if (new_str == NULL)
		return (-1);
	i = i + add_word(token, new_str);
	free(new_str);
	return (i);
}

t_token	*add_new_token(t_token *token)
{
	token->next = (t_token *)malloc(sizeof(t_token));
	if (token->next == 0)
		return (NULL);
	token = token->next;
	token->next = NULL;
	return (token);
}
