/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:00:15 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 21:24:46 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocate_words(t_pipes *pipe, t_num *num)
{
	t_cmd	*cmd;

	cmd = pipe->simple_cmd;
	cmd->word = (char **)malloc(sizeof(char *) * (num->word_num + 1));
	if (cmd->word == NULL)
		return ;
	cmd->word[num->word_num] = NULL;
	cmd->redirection = (char **)malloc(sizeof(char *) * (num->re_num + 1));
	if (cmd->redirection == NULL)
		return ;
	cmd->redirection[num->re_num] = NULL;
	cmd->redir_value = (char **)malloc(sizeof(char *) * (num->re_word + 1));
	if (cmd->redir_value == NULL)
		return ;
	cmd->redir_value[num->re_word] = NULL;
}

void	input_component(t_shell *ms, t_token *token)
{
	t_token	*tmp;
	t_pipes	*pipe;
	t_num	num;

	tmp = token;
	pipe = ms->head;
	ft_memset(&num, 0, sizeof(t_num));
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			allocate_words(pipe, &num);
			pipe = pipe->next;
			ft_memset(&num, 0, sizeof(t_num));
		}
		else if (tmp->type == WORD || tmp->type == HEREDOC)
			increase_num(&num);
		else if (tmp->type == REDIRECTION)
		{
			num.re_flag = 1;
			num.re_num++;
		}
		tmp = tmp->next;
	}
	allocate_words(pipe, &num);
}

void	copy_word(t_num *num, t_pipes *pipe, t_token *tmp)
{
	if (num->re_flag == 1)
	{
		pipe->simple_cmd->redir_value[num->re_word] = ft_strdup(tmp->value);
		num->re_word++;
	}
	else
	{
		pipe->simple_cmd->word[num->word_num] = ft_strdup(tmp->value);
		num->word_num++;
	}
	num->re_flag = 0;
}

void	dup_component(t_shell *ms, t_token *token)
{
	t_pipes	*pipe;
	t_token	*tmp;
	t_num	num;

	pipe = ms->head;
	tmp = token;
	ft_memset(&num, 0, sizeof(t_num));
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			pipe = pipe->next;
			ft_memset(&num, 0, sizeof(t_num));
		}
		else if (tmp->type == WORD || tmp->type == HEREDOC)
			copy_word(&num, pipe, tmp);
		else if (tmp->type == REDIRECTION)
		{
			pipe->simple_cmd->redirection[num.re_num] = ft_strdup(tmp->value);
			num.re_num++;
			num.re_flag = 1;
		}
		tmp = tmp->next;
	}
}

void	make_simple_command(t_token *token, t_shell *ms)
{
	make_pipes(token, ms);
	input_component(ms, token);
	dup_component(ms, token);
}
