/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:45:32 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 23:11:38 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_quote_special(t_tmp *str, t_token *token, int idx, int i)
{
	int	len;

	if (token->value[i] == '?')
	{
		len = question_env(str, token, idx);
		return (len);
	}
	else if (token->value[i] == '*')
	{
		delete_envwild(str, token, idx, i);
		return (0);
	}
	else if (!(ft_isalpha(token->value[i]) || token->value[i] == '_'))
		return (1);
	return (-1);
}

void	none_env(t_token *token, int idx, int i)
{
	t_tmp	str;

	str.tmp = ft_substr(token->value, 0, idx);
	str.tmp2 = ft_substr(token->value, i, ft_strlen(token->value) - i);
	str.tmp3 = ft_strjoin(str.tmp, str.tmp2);
	free_three(str.tmp, str.tmp2, token->value);
	token->value = str.tmp3;
}

int	allocate_env_quote(t_shell *ms, t_token *token, int idx, int i)
{
	char	*env;
	char	*f_env;
	t_tmp	str;

	env = (char *)malloc(sizeof(char) * (i - idx));
	if (env == NULL)
		return (-1);
	ft_strlcpy(env, token->value + idx + 1, i - idx);
	f_env = find_value(env, ms);
	free(env);
	if (f_env == NULL || ft_strcmp(f_env, "") == 0)
	{
		none_env(token, idx, i);
		return (0);
	}
	str.tmp = ft_substr(token->value, 0, idx);
	str.tmp2 = ft_strjoin(str.tmp, f_env);
	free(str.tmp);
	str.tmp3 = ft_substr(token->value, i, ft_strlen(token->value) - i);
	str.tmp = ft_strjoin(str.tmp2, str.tmp3);
	free_three(token->value, str.tmp2, str.tmp3);
	token->value = str.tmp;
	return (ft_strlen(f_env) - 1);
}

int	replace_env_quote(t_token *token, t_shell *ms, int idx)
{
	t_tmp	str;
	int		i;
	int		len;

	i = idx + 1;
	len = check_env_quote_special(&str, token, idx, i);
	if (len != -1)
		return (len);
	while (token->value[i] && is_env(token->value[i]))
		i++;
	if (idx + 1 == i)
		return (1);
	len = allocate_env_quote(ms, token, idx, i);
	return (len);
}
