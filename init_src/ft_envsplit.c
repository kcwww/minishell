/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:07:32 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/05 17:33:54 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **ft_envsplit(char *env)
{
    int     i;
    char    **copy_env;

    i = 0;
    copy_env = (char **)malloc(sizeof(char *) * 3);
    if (copy_env == NULL)
        return (NULL);
    copy_env[2] = NULL;
    while (env[i])
    {
        if (env[i] == '=')
            break ;
        i++;
    }
    copy_env[0] = (char *)malloc(sizeof(char) * (i + 1));
    if (copy_env[0] == NULL)
        return (NULL);
    copy_env[0][i] = 0;
    copy_env[1] = (char *)malloc(sizeof(char) * (ft_strlen(env) - i));
    if (copy_env[1] == NULL)
        return (NULL);
    copy_env[1][ft_strlen(env) - i - 1] = 0;
    i = 0;
    while (env[i])
    {
        if (env[i] == '=')
            break;
        copy_env[0][i] = env[i];
        i++;
    }
    i++;
    int j = 0;
    while (env[i])
    {
        copy_env[1][j] = env[i];
        i++;
        j++;
    }
    return (copy_env);
}