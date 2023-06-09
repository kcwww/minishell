/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:07:32 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 23:25:56 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal_sign(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	return (i);
}

void	copy_strings(char *source, char *dest, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		dest[i] = source[start];
		i++;
		start++;
	}
	dest[i] = '\0';
}

char	**ft_envsplit(char *env)
{
	int		equal_sign_index;
	char	**copy_env;

	equal_sign_index = find_equal_sign(env);
	copy_env = (char **)malloc(sizeof(char *) * 3);
	if (copy_env == NULL)
	{
		return (NULL);
	}
	copy_env[0] = (char *)malloc(sizeof(char) * (equal_sign_index + 1));
	copy_env[1] = (char *)malloc(sizeof(char) * \
	(ft_strlen(env) - equal_sign_index));
	if (copy_env[0] == NULL || copy_env[1] == NULL)
	{
		return (NULL);
	}
	copy_strings(env, copy_env[0], 0, equal_sign_index);
	copy_strings(env, copy_env[1], equal_sign_index + 1, ft_strlen(env));
	copy_env[2] = NULL;
	return (copy_env);
}
