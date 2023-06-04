/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:24:53 by dkham             #+#    #+#             */
/*   Updated: 2023/06/04 15:24:54 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_shell *my_shell, t_pipes *head, char **env, int i)
{
	set_signal_child();
	handle_input_redirection(my_shell, i);
	handle_output_redirection(my_shell);
	if (is_builtin(head->simple_cmd->word[0]))
	{
		builtin(my_shell, head);
		exit(0);
	}
	else
		handle_external_command(my_shell, head, env);
	exit(1);
}

void	parent_process(t_shell *my_shell, int i)
{
	set_parent_signal();
	if (my_shell->fd_in != 0)
		close(my_shell->fd_in);
	if (my_shell->fd_out != 1)
		close(my_shell->fd_out);
	if (my_shell->pipe_fd[1] != 1)
		close(my_shell->pipe_fd[1]);
	if (i != 1 && my_shell->prev_pipe_fd_0 != -1)
		close(my_shell->prev_pipe_fd_0);
	my_shell->prev_pipe_fd_0 = my_shell->pipe_fd[0];
}
