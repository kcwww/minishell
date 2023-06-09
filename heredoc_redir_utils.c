/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:35 by dkham             #+#    #+#             */
/*   Updated: 2023/06/09 15:40:45 by dkham            ###   ########.fr       */
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
