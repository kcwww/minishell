/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:31:20 by dkham             #+#    #+#             */
/*   Updated: 2023/06/10 00:49:26 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredocs(t_shell *my_shell)
{
	t_pipes	*head;
	int		i;
	char	*tmpfile;

	head = my_shell->head;
	while (head)
	{
		i = 0;
		while (head->simple_cmd->redirection && \
		head->simple_cmd->redirection[i])
		{
			if (ft_strcmp(head->simple_cmd->redirection[i], "<<") == 0)
			{
				tmpfile = ft_strjoin("/tmp/", head->simple_cmd->redir_value[i]);
				make_hd(my_shell, tmpfile, head->simple_cmd->redir_value[i]);
				free(head->simple_cmd->redirection[i]);
				head->simple_cmd->redirection[i] = ft_strdup("<");
				free(head->simple_cmd->redir_value[i]);
				head->simple_cmd->redir_value[i] = ft_strdup(tmpfile);
				free(tmpfile);
			}
			i++;
		}
		head = head->next;
	}
}

int	save_stdin_and_set_signal(t_shell *my_shell)
{
	set_heredoc_signal(my_shell);
	return (dup(0));
}

void	make_hd(t_shell *my_shell, char *filename, char *end_str)
{
	int		fd;
	int		save_stdin;
	char	*line;

	my_shell->heredoc_used = 1;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	save_stdin = save_stdin_and_set_signal(my_shell);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, end_str) == 0)
			break ;
		else if (line == NULL)
		{
			dup2(save_stdin, 0);
			g_exit_status = 130;
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	init_signal(my_shell);
	close(fd);
}

void	cleanup_heredocs(t_shell *my_shell)
{
	int		i;
	t_pipes	*head;

	i = 0;
	head = my_shell->head;
	while (head)
	{
		if (my_shell->head->simple_cmd->redir_value[i])
		{
			if (ft_strncmp(my_shell->head->simple_cmd->redir_value[i], \
			"/tmp/", 5) == 0)
				unlink(my_shell->head->simple_cmd->redir_value[i]);
		}
		head = head->next;
	}
}

void	handle_redirections(t_shell *my_shell, t_pipes	*head)
{
	int	i;
	int	fd;

	i = 0;
	while (head->simple_cmd->redirection[i])
	{
		if (ft_strcmp(head->simple_cmd->redirection[i], "<") == 0)
		{
			fd = open(head->simple_cmd->redir_value[i], O_RDONLY);
			if (fd < 0)
				print_error_message(head->simple_cmd->redir_value[i]);
			else
				my_shell->fd_in = fd;
		}
		else if (ft_strcmp(head->simple_cmd->redirection[i], ">") == 0 && \
		fd >= 0)
			output_redir(my_shell, head, i, 0);
		else if (ft_strcmp(head->simple_cmd->redirection[i], ">>") == 0 && \
		fd >= 0)
			output_redir(my_shell, head, i, 1);
		i++;
	}
	head = head->next;
	return ;
}
