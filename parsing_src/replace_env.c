/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:42:11 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 22:43:15 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_envwild(t_tmp *str, t_token *token, int idx, int i)
{
	str->tmp = ft_substr(token->value, 0, idx);
	str->tmp2 = ft_substr(token->value, i + 1, ft_strlen(token->value) - i - 1);
	str->tmp3 = ft_strjoin(str->tmp, str->tmp2);
	free_three(str->tmp, str->tmp2, token->value);
	token->value = str->tmp3;
}

int	check_env_special(t_tmp *str, t_token *token, int idx, int i)
{
	int	len;

	if (token->value[i] == '?')
	{
		len = question_env(str, token, idx);
		return (len);
	}
	else if (token->value[i] == '\'' || token->value[i] == '\"')
	{
		delete_env_and_quote(str, token, idx, i);
		return (0);
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

int	check_finded_env(char *f_env, t_tmp *str, t_token *token, char *env)
{
	int	len;

	if (f_env == NULL || ft_strcmp(f_env, "") == 0)
	{
		token->value = ft_strjoin(str->tmp, str->tmp3);
		token->type = -1;
		free_three(str->tmp, str->tmp3, NULL);
		len = 0;
		free(env);
	}
	else
	{
		f_env = check_env(f_env, token);
		str->tmp2 = ft_strjoin(str->tmp, f_env);
		free(str->tmp);
		str->tmp = ft_strjoin(str->tmp2, str->tmp3);
		token->value = str->tmp;
		len = ft_strlen(f_env);
		free_three(f_env, str->tmp2, str->tmp3);
		free(env);
	}
	return (len);
}

int	allocate_env(t_tmp *str, t_token *token, t_shell *ms, int *arr)
{
	int		len;
	char	*env;
	char	*f_env;

	len = arr[0] - arr[1] - 1;
	env = (char *)malloc(sizeof(char) * (len + 1));
	if (env == NULL)
		return (-1);
	ft_strlcpy(env, token->value + arr[1] + 1, len + 1);
	f_env = find_value(env, ms);
	free(token->value);
	len = check_finded_env(f_env, str, token, env);
	return (len);
}

int	replace_env(t_token *token, t_shell *ms, int idx)
{
	int		i;
	int		len;
	int		arr[2];
	t_tmp	str;

	i = idx + 1;
	len = check_env_special(&str, token, idx, i);
	if (len != -1)
		return (len);
	while (token->value[i] && is_env(token->value[i]))
		i++;
	if ((idx + 1) == i)
		return (1);
	str.tmp = ft_substr(token->value, 0, idx);
	str.tmp3 = ft_substr(token->value, i, ft_strlen(token->value) - i);
	len = i - idx - 1;
	arr[0] = i;
	arr[1] = idx;
	len = allocate_env(&str, token, ms, arr);
	return (len);
}
