/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:43:56 by dkham             #+#    #+#             */
/*   Updated: 2023/06/05 20:16:18 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_shell *my_shell, char **env)
{
	t_pipes	*head;
	int		i;
	pid_t	pid;

	i = 0;
	head = my_shell->head;
	init_fd(my_shell);
	handle_heredocs(my_shell);
	while (head)
	{
		pid = handle_proc(my_shell, head, env, i);
		head = head->next;
		i++;
	}
	if (my_shell->heredoc_used == 1)
		cleanup_heredocs(my_shell);
	if (!(i == 1 && is_builtin(my_shell->head->simple_cmd->word[0]) \
	&& !my_shell->head->next))
		wait_for_children(i, pid, my_shell);
}

void	init_fd(t_shell *my_shell)
{
	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	my_shell->pipe_fd[0] = 0;
	my_shell->pipe_fd[1] = 1;
	my_shell->prev_pipe_fd_0 = -1;
	my_shell->last_cmd_flag = 0;
	my_shell->heredoc_used = 0;
}

pid_t	handle_proc(t_shell *my_shell, t_pipes *head, char **env, int i)
{
	pid_t	pid;

	prepare_fd(my_shell, head);
	handle_redirections(my_shell, head);
	if (head->simple_cmd->word[0] == NULL && my_shell->heredoc_used == 1)
		return (-1);
	if (!head->next && is_builtin(head->simple_cmd->word[0]) && i == 0)
	{
		builtin(my_shell, head);
		return (-1);
	}
	else
	{
		if (head->next && pipe(my_shell->pipe_fd) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		else if (pid == 0)
			child_process(my_shell, head, env, ++i);
		else
			parent_process(my_shell, ++i);
		return (pid);
	}
}

void	prepare_fd(t_shell *my_shell, t_pipes *head)
{
	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	if (head->next == NULL)
		my_shell->last_cmd_flag = 1;
}

void	wait_for_children(int i, pid_t pid, t_shell *my_shell)
{
	pid_t	exited_pid;
	int		status;

	while (i--)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (exited_pid == pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit_status = 128 + WTERMSIG(status); 
				check_signum(g_exit_status);
			}
		}
	}
	init_signal(my_shell);
}
