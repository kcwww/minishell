/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:10:45 by kcw               #+#    #+#             */
/*   Updated: 2023/06/04 22:10:47 by kcw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_simple_command(t_token *token, t_shell *ms)
{
	int		pipes;
	int		re_flag;
	t_token	*tmp;
	t_pipes	*pipe;


	tmp = token;

	pipes = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipes++;
		tmp = tmp->next;
	}




	pipe = (t_pipes *)malloc(sizeof(t_pipes));
	if (pipe == NULL)
		return ;
	ms->head = pipe;
	pipe->simple_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (pipe->simple_cmd == NULL)
		return ;
	ft_memset(pipe->simple_cmd, 0, sizeof(t_cmd));


	while (pipes > 0)
	{
		pipe->next = (t_pipes *)malloc(sizeof(t_pipes));
		if (pipe->next == NULL)
			return ;
		pipe = pipe->next;
		pipe->simple_cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (pipe->simple_cmd == NULL)
			return ;
		ft_memset(pipe->simple_cmd, 0, sizeof(t_cmd));
		pipes--;
	}
	pipe->next = NULL;



	pipe = ms->head;

	tmp = token;
	re_flag = 0;
	int		re_num = 0;
	int		re_word = 0;
	int		word_num = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{


			pipe->simple_cmd->word = (char **)malloc(sizeof(char *) * (word_num + 1));
			if (pipe->simple_cmd->word == NULL)
				return ;
			pipe->simple_cmd->word[word_num] = NULL;
			pipe->simple_cmd->redirection = (char **)malloc(sizeof(char *) * (re_num + 1));
			if (pipe->simple_cmd->redirection == NULL)
				return ;
			pipe->simple_cmd->redirection[re_num] = NULL;
			pipe->simple_cmd->redir_value = (char **)malloc(sizeof(char *) * (re_word + 1));
			if (pipe->simple_cmd->redir_value == NULL)
				return ;
			pipe->simple_cmd->redir_value[re_word] = NULL;
			pipe = pipe->next;
			re_flag = 0;
			re_num = 0;
			re_word = 0;
			word_num = 0;
		}
		else if (tmp->type == WORD)
		{
			if (re_flag == 1)
				re_word++;
			else
				word_num++;
			re_flag = 0;
		}
		else if (tmp->type == REDIRECTION)
		{
			re_flag = 1;
			re_num++;
		}
		tmp = tmp->next;
	}

	pipe->simple_cmd->word = (char **)malloc(sizeof(char *) * (word_num + 1));
	if (pipe->simple_cmd->word == NULL)
		return ;
	pipe->simple_cmd->word[word_num] = NULL;
	pipe->simple_cmd->redirection = (char **)malloc(sizeof(char *) * (re_num + 1));
	if (pipe->simple_cmd->redirection == NULL)
		return ;
	pipe->simple_cmd->redirection[re_num] = NULL;
	pipe->simple_cmd->redir_value = (char **)malloc(sizeof(char *) * (re_word + 1));
	if (pipe->simple_cmd->redir_value == NULL)
		return ;
	pipe->simple_cmd->redir_value[re_word] = NULL;

	pipe = ms->head;
	tmp = token;
	re_flag = 0;
	re_num = 0;
	re_word = 0;
	word_num = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			pipe = pipe->next;
			re_flag = 0;
			re_num = 0;
			re_word = 0;
			word_num = 0;
		}
		else if (tmp->type == WORD || tmp->type == HEREDOC)
		{
			if (re_flag == 1)
			{
				pipe->simple_cmd->redir_value[re_word] = ft_strdup(tmp->value);
				re_word++;
			}
			else
			{
				pipe->simple_cmd->word[word_num] = ft_strdup(tmp->value);
				word_num++;
			}
			re_flag = 0;
		}
		else if (tmp->type == REDIRECTION)
		{
			pipe->simple_cmd->redirection[re_num] = ft_strdup(tmp->value);
			re_num++;
			re_flag = 1;
		}
		tmp = tmp->next;
	}
}
