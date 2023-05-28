/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:32:23 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/28 18:05:15 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_env(t_token *token, t_shell *ms)
{
	t_token	*start;
	int		i;

	start = token;
	while (start)
	{
		printf("token.type: %d value %s\n", start->type, start->value);
		start = start->next;
	}
	printf("tokenizer end\n\n\n");
	usleep(100000);
	(void)ms;

	// 환경변수 -> 따옴표
	// 따옴표 -> 환경변수
	// 이렇게 모두 검사해야함

	start = token;
	while (start)
	{
		i = 0;
		while (start->value[i])
		{
			if (start->value[i] == '\'')
			{
				delete_single_quote(start);
				break;
			}
			else if (start->value[i] == '\"')
			{
				break ;
			}
			else if (start->value[i] == '$')
			{
				printf("%s\n",start->value);
				break ;
			}
			i++;
		}
		start = start->next;
	}
}
