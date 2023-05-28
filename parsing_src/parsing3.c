/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:32:23 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/28 16:34:36 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_env(t_token *token, t_shell *ms)
{
	while (token)
	{
		printf("token.type: %d\n", token->type);
		printf("token.value: %s\n", token->value);
		token = token->next;
	}
	printf("tokenizer end\n\n\n");
	usleep(100000);
	(void)ms;
}
