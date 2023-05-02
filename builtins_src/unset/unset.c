/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:33:13 by dkham             #+#    #+#             */
/*   Updated: 2023/05/02 21:53:57 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// unset with no options

// void	unset(char **args, t_execute **execute)
// {
// 	int		i;
// 	int		j;
// 	char	**new_env;

// 	i = 0;
// 	j = 0;
// 	while (args[i])
// 		i++;
// 	if (i == 1)
// 	{
// 		ft_putstr_fd("unset: not enough arguments\n", (*execute)->fd_out);
// 		return ;
// 	}
// 	new_env = malloc(sizeof(char *) * (i));
// 	i = 1;
// 	while (args[i])
// 	{
// 		while ((*execute)->env[j])
// 		{
// 			if (ft_strncmp(args[i], (*execute)->env[j], ft_strlen(args[i])) != 0)
// 				new_env[j] = ft_strdup((*execute)->env[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_env[j] = NULL;
// 	free_array((*execute)->env);
// 	(*execute)->env = new_env;
// }
