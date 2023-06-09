/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:23:44 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 21:24:50 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increase_num(t_num *num)
{
	if (num->re_flag == 1)
		num->re_word++;
	else
		num->word_num++;
	num->re_flag = 0;
}

int	count_pipes(t_token *token)
{
	t_token	*tmp;
	int		pipes;

	tmp = token;
	pipes = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipes += 1;
		tmp = tmp->next;
	}
	return (pipes);
}

t_pipes	*create_pipes(void)
{
	t_pipes	*pipe;

	pipe = (t_pipes *)malloc(sizeof(t_pipes));
	if (pipe == NULL)
		return (NULL);
	pipe->simple_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (pipe->simple_cmd == NULL)
		return (NULL);
	ft_memset(pipe->simple_cmd, 0, sizeof(t_cmd));
	return (pipe);
}

void	make_pipes(t_token *token, t_shell *ms)
{
	int		pipes;
	t_pipes	*pipe;

	pipes = count_pipes(token);
	pipe = create_pipes();
	ms->head = pipe;
	while (pipes > 0)
	{
		pipe->next = create_pipes();
		pipe = pipe->next;
		pipes--;
	}
	pipe->next = NULL;
}
