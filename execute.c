/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:39:01 by dkham             #+#    #+#             */
/*   Updated: 2023/05/28 16:33:11 by dkham            ###   ########.fr       */
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
	handle_heredocs(my_shell); // 자식프로세스 확인
	while (head)
	{
		pid = handle_proc(my_shell, head, env, i); // 히어독 후 exit 등으로 빠져나갔을 때 free 못해 leak 발생
		head = head->next;
		i++;
	}
	if (my_shell->heredoc_used == 1)
		cleanup_heredocs(my_shell);
	wait_for_children(i, pid);
}

void	init_fd(t_shell *my_shell)
{
	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	my_shell->pipe_fd[0] = 0;
	my_shell->pipe_fd[1] = 1;
	my_shell->prev_pipe_fd_0 = 0;
	my_shell->last_cmd_flag = 0;
	my_shell->heredoc_used = 0;
}

pid_t	handle_proc(t_shell *my_shell, t_pipes *head, char **env, int i)
{
	pid_t	pid;

	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	if (head->next == NULL)
		my_shell->last_cmd_flag = 1;
	handle_redirections(my_shell, head);
	if (head->simple_cmd->word[0] == NULL) // heredoc인 경우 word 가 없음 / 자식으로 들어가지 않고, 바로 리턴 (새로 추가)
		return (-1);
	if (!head->next && is_builtin(head->simple_cmd->word[0]))
	{
		builtin(my_shell);
		return (-1);
	}
	else
	{
		if (head->next && pipe(my_shell->pipe_fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			child_process(my_shell, head, env, ++i);
		else
			parent_process(my_shell, ++i);
		return (pid);
	}
}

void	wait_for_children(int i, pid_t pid)
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
				g_exit_status = WTERMSIG(status);
		}
	}
}
