/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:42:11 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/03 17:59:43 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env(char *env, t_shell *ms, t_token *token)
{
	int		i;
	char	**tmp;
	char	*re;
	t_token	*new_token;
	t_token	*tmp_token;
	(void)env;
	(void)ms;

	tmp = ft_split(env, ' '); // NULL GUARD

	re = ft_strdup(tmp[0]); // NULL GUARD
	i = 1;
	tmp_token = token->next;
	while (tmp[i])
	{
		new_token = (t_token *)malloc(sizeof(t_token)); // NULL GUARD
		new_token->value = ft_strdup(tmp[i]); // NULL GUARD
		new_token->type = WORD;
		new_token->next = NULL;
		token->next = new_token;
		token = token->next;
		i++;
	}
	token->next = tmp_token;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (re);
}

int	replace_env(t_token *token, t_shell *ms)
{
	int		i;
	int		start;
	int		len;
	char	*env;
	char	*f_env;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	len = 0;
	start = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			i++;
			if (token->value[i] == '?')
			{
				tmp = ft_substr(token->value, 0, i - 1);
				tmp2 = ft_itoa(g_exit_status);
				len = ft_strlen(tmp2);
				tmp3 = ft_strjoin(tmp, tmp2);
				free(tmp);
				free(tmp2);
				tmp = ft_substr(token->value, i + 1, ft_strlen(token->value));
				tmp2 = ft_strjoin(tmp3, tmp);
				free(tmp3);
				free(tmp);
				free(token->value);
				token->value = tmp2;
				return (len);
			}
			else if (token->value[i] == '\'' || token->value[i] == '\"')
			{
				tmp = ft_substr(token->value, 0, i - 1);
				tmp2 = ft_substr(token->value, i, ft_strlen(token->value) - i);
				tmp3 = ft_strjoin(tmp, tmp2);
				free(tmp);
				free(tmp2);
				free(token->value);
				token->value = tmp3;
				return (0);
			}
			start = i;
			while (token->value[i] && token->value[i] != ' ' && token->value[i] != '\'' && \
				token->value[i] != '\"' && token->value[i] != '$')
					i++;

			if (start == i)
				return (1);
			tmp = ft_substr(token->value, 0, start - 1);
			tmp3 = ft_substr(token->value, i, ft_strlen(token->value));
			len = i - start;
			break ;
		}
		i++;
	}
	env = (char *)malloc(sizeof(char) * (len + 1)); // NULL GUARD
	env[start] = 0;
	ft_strlcpy(env, token->value + start, len + 1);
	f_env = find_value(env, ms);
	free(token->value);
	if (f_env == NULL || ft_strcmp(f_env, "") == 0)
	{
		token->value = ft_strjoin(tmp, tmp3);
		token->type = -1;
		free(tmp);
		free(tmp3);
		len = 0;
	}
	else
	{
		f_env = check_env(f_env, ms, token);
		tmp2 = ft_strjoin(tmp, f_env);
		free(tmp);
		tmp = ft_strjoin(tmp2, tmp3);
		free(tmp2);
		free(tmp3);
		token->value = tmp;
		len = ft_strlen(f_env);
		free(f_env);
	}
	free(env);
	return (len);
}
