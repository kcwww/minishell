/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:45:32 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/03 17:59:08 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_env_quote(t_token *token, t_shell *ms, int idx)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*env;
	char	*f_env;
	int		i;
	int		len;

	i = idx + 1;
	if (token->value[i] == '?')
	{
		tmp = ft_substr(token->value, 0, idx);
		tmp2 = ft_itoa(g_exit_status);
		len = ft_strlen(tmp2);
		tmp3 = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		tmp = ft_substr(token->value, i + 1, ft_strlen(token->value) - i - 1);
		tmp2 = ft_strjoin(tmp3, tmp);
		free(tmp3);
		free(tmp);
		free(token->value);
		token->value = tmp2;
		return (len);
	}
	while (token->value[i] && token->value[i] != ' ' && token->value[i] != '\'' && \
		token->value[i] != '\"' && token->value[i] != '$')
		i++;
	if (idx + 1 == i) //"$"
		return (1);
	env = (char *)malloc(sizeof(char) * (i - idx)); // NULL GUARD
	ft_strlcpy(env, token->value + idx + 1, i - idx);
	f_env = find_value(env, ms);
	free(env);
	if (f_env == NULL || ft_strcmp(f_env, "") == 0)
	{
		tmp = ft_substr(token->value, 0, idx);
		tmp2 = ft_substr(token->value, i, ft_strlen(token->value) - i);
		tmp3 = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		free(token->value);
		token->value = tmp3;
		return (0);
	}
	tmp = ft_substr(token->value, 0, idx);
	tmp2 = ft_strjoin(tmp, f_env);
	free(tmp);
	tmp3 = ft_substr(token->value, i, ft_strlen(token->value) - i);
	tmp = ft_strjoin(tmp2, tmp3);
	free(tmp2);
	free(tmp3);
	free(token->value);
	token->value = tmp;
	return (ft_strlen(f_env) - 1);
}