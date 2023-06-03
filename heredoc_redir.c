/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:46:08 by dkham             #+#    #+#             */
/*   Updated: 2023/06/03 19:20:34 by dkham            ###   ########.fr       */
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

void	make_hd(t_shell *my_shell, char *filename, char *end_str)
{
	int		fd;
	char	*line;

	my_shell->heredoc_used = 1;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, end_str) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
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
	int		i;
	int		fd;

	i = 0;
	while (head->simple_cmd->redirection[i])
	{
		if (ft_strcmp(head->simple_cmd->redirection[i], "<") == 0)
		{
			fd = open(head->simple_cmd->redir_value[i], O_RDONLY);
			if (fd < 0)
				print_error_message(head->simple_cmd->redir_value[i]);
			my_shell->fd_in = fd;
		}
		else if (ft_strcmp(head->simple_cmd->redirection[i], ">") == 0)
		{
			fd = open(head->simple_cmd->redir_value[i], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				print_error_message(head->simple_cmd->redir_value[i]);
			my_shell->fd_out = fd;
		}
		i++;
	}
	head = head->next;
	return ;
}

void	print_error_message(char *value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
