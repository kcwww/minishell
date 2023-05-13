/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:03:31 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/13 12:09:41 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *ms)
{
	t_pipes	*pipe;
	t_pipes	*tmp;
	t_cmd	*cmd;
	int		i;

	pipe = ms->head;
	while (pipe)
	{
		cmd = pipe->simple_cmd;
		i = 0;
		while (cmd->word[i])
		{
			free(cmd->word[i]);
			i++;
		}
		free(cmd->word);
		i = 0;
		while (cmd->redirection[i])
		{
			free(cmd->redirection[i]);
			i++;
		}
		free(cmd->redirection);
		i = 0;
		while (cmd->redir_value[i])
		{
			free(cmd->redir_value[i]);
			i++;
		}
		free(cmd->redir_value);
		free(cmd);
		tmp = pipe;
		pipe = pipe->next;
		free(tmp);
	}
}
