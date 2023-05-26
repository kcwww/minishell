/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:59:56 by dkham             #+#    #+#             */
/*   Updated: 2023/05/26 21:04:16 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_simple_command(t_token *token, t_shell *ms)
{
	int		i;
	int		pipes;
	int		re_flag;
	t_token	*tmp;
	t_pipes	*pipe;


	tmp = token;

	i = 0;
	pipes = 0;
	while (tmp)
	{
		// if (i == 0 && tmp->type == PIPE)
		// {
		// 	printf("pipe error\n"); //delete
		// 	return ;
		// }
		if (tmp->type == PIPE)
			pipes++;
		tmp = tmp->next;
		i++;
	}
	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	// if (tmp->type == PIPE)
	// 	return ;



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
			// pipe->simple_cmd->fd_in = 0;
			// pipe->simple_cmd->fd_out = 1;
			// pipe->simple_cmd->pipe_fd[0] = 0;
			// pipe->simple_cmd->pipe_fd[1] = 1;
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
		else if (tmp->type == WORD)
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

	// tmp = token;
	// while (tmp)
	// {
	// 	printf("type: %d ", tmp->type);
	// 	printf("value: %s\n", tmp->value);
	// 	tmp = tmp->next;
	// }

	// pipe = ms->head;
	// while (pipe)
	// {
	// 	int j = 0;
	// 	while (pipe->simple_cmd->word[j])
	// 	{
	// 		printf("word: %s\n", pipe->simple_cmd->word[j]);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	while (pipe->simple_cmd->redirection[j])
	// 	{
	// 		printf("redirection: %s\n", pipe->simple_cmd->redirection[j]);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	while (pipe->simple_cmd->redir_value[j])
	// 	{
	// 		printf("redir_value: %s\n", pipe->simple_cmd->redir_value[j]);
	// 		j++;
	// 	}
	// 	pipe = pipe->next;
	// 	printf("next\n");
	// }
}
