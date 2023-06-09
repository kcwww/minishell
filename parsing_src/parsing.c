/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:34:00 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 19:54:27 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_tokens(t_token *start)
{
	t_token	*token;

	while (start)
	{
		token = start->next;
		free(start->value);
		free(start);
		start = token;
	}
}

int	process_tokens(t_token **token, char *str, int i)
{
	i = skip_spaces(str, i);
	if (str[i] == '\0')
		return (-1);
	i = process_new_string(*token, str, i);
	if (i == -1)
		return (-1);
	i = skip_spaces(str, i);
	if (str[i] == '\0')
		return (-1);
	*token = add_new_token(*token);
	if (*token == NULL)
		return (-1);
	return (i);
}

void	tokenizer(char *str, t_shell *ms)
{
	t_token	*token;
	t_token	*start;
	int		i;

	i = 0;
	token = create_token();
	if (token == NULL)
		return ;
	start = token;
	while (i < ft_strlen(str))
	{
		i = process_tokens(&token, str, i);
		if (i == -1)
			break ;
	}
	check_token(start, ms);
	make_simple_command(start, ms);
	cleanup_tokens(start);
}

void	check_pipes(t_shell *ms)
{
	t_pipes	*pipe;

	pipe = ms->head;
	while (pipe)
	{
		if (pipe->simple_cmd->word[0] == NULL && \
		pipe->simple_cmd->redirection[0] == NULL)
		{
			printf("bash: syntax error\n");
			ms->error = 1;
			g_exit_status = 2;
			return ;
		}
		if (pipe->simple_cmd->redirection[0] != NULL && \
		pipe->simple_cmd->redir_value[0] == NULL)
		{
			printf("bash: syntax error\n");
			ms->error = 1;
			g_exit_status = 2;
			return ;
		}
		pipe = pipe->next;
	}
}

void	parsing_start(char *str, t_shell *ms)
{
	ms->error = 0;
	tokenizer(str, ms);
	check_pipes(ms);
}
