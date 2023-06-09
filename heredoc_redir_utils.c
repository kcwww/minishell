/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:35 by dkham             #+#    #+#             */
/*   Updated: 2023/06/09 23:38:28 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(char *value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	g_exit_status = 1;
}

void	output_redir(t_shell *my_shell, t_pipes *head, int i, int append)
{
	int	fd;

	if (append)
		fd = open(head->simple_cmd->redir_value[i], O_WRONLY | O_CREAT | \
		O_APPEND, 0644);
	else
		fd = open(head->simple_cmd->redir_value[i], O_WRONLY | O_CREAT | \
		O_TRUNC, 0644);
	if (fd < 0)
		print_error_message(head->simple_cmd->redir_value[i]);
	else
		my_shell->fd_out = fd;
}
