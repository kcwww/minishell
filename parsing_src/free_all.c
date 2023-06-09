/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:03:31 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 20:42:46 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_word(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->word[i])
	{
		free(cmd->word[i]);
		i++;
	}
	free(cmd->word);
}

void	free_redirection(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redirection[i])
	{
		free(cmd->redirection[i]);
		i++;
	}
	free(cmd->redirection);
}

void	free_redir_value(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redir_value[i])
	{
		free(cmd->redir_value[i]);
		i++;
	}
	free(cmd->redir_value);
}

void	free_all(t_shell *ms)
{
	t_pipes	*pipe;
	t_pipes	*tmp;
	t_cmd	*cmd;

	pipe = ms->head;
	while (pipe)
	{
		cmd = pipe->simple_cmd;
		free_word(cmd);
		free_redirection(cmd);
		free_redir_value(cmd);
		free(cmd);
		tmp = pipe;
		pipe = pipe->next;
		free(tmp);
	}
}
