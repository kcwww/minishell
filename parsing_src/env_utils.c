/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:05:30 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 23:20:43 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

t_token	*create_word_token(char *tmp)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = ft_strdup(tmp);
	if (new_token->value == NULL)
		return (NULL);
	new_token->type = WORD;
	new_token->next = NULL;
	return (new_token);
}

char	*check_env(char *env, t_token *token)
{
	int		i;
	char	**tmp;
	char	*re;
	t_token	*new_token;
	t_token	*tmp_token;

	tmp = ft_split(env, ' ');
	if (tmp == NULL)
		return (NULL);
	re = ft_strdup(tmp[0]);
	if (re == NULL)
		return (NULL);
	i = 1;
	tmp_token = token->next;
	while (tmp[i])
	{
		new_token = create_word_token(tmp[i]);
		token->next = new_token;
		token = token->next;
		i++;
	}
	token->next = tmp_token;
	free_str(tmp);
	return (re);
}

int	question_env(t_tmp *str, t_token *token, int idx)
{
	int	len;
	int	i;

	i = idx + 1;
	str->tmp = ft_substr(token->value, 0, idx);
	str->tmp2 = ft_itoa(g_exit_status);
	len = ft_strlen(str->tmp2);
	str->tmp3 = ft_strjoin(str->tmp, str->tmp2);
	free_three(str->tmp, str->tmp2, NULL);
	str->tmp = ft_substr(token->value, i + 1, ft_strlen(token->value) - i - 1);
	str->tmp2 = ft_strjoin(str->tmp3, str->tmp);
	free_three(str->tmp3, str->tmp, token->value);
	token->value = str->tmp2;
	return (len);
}

void	delete_env_and_quote(t_tmp *str, t_token *token, int idx, int i)
{
	str->tmp = ft_substr(token->value, 0, idx);
	str->tmp2 = ft_substr(token->value, i, ft_strlen(token->value) - i);
	str->tmp3 = ft_strjoin(str->tmp, str->tmp2);
	free_three(str->tmp, str->tmp2, token->value);
	token->value = str->tmp3;
}
