/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:18:34 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 23:18:42 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_signal(t_shell *my_shell)
{
	my_shell->sa_sigint.sa_handler = sigint_handler;
	my_shell->sa_sigquit.sa_handler = SIG_IGN;
	my_shell->sa_sigint.sa_flags = 0;
	my_shell->sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &my_shell->sa_sigint, NULL);
	sigaction(SIGQUIT, &my_shell->sa_sigquit, NULL);
}

void	set_parent_signal(t_shell *my_shell)
{
	my_shell->sa_sigint.sa_handler = SIG_IGN;
	my_shell->sa_sigquit.sa_handler = SIG_IGN;
	my_shell->sa_sigint.sa_flags = 0;
	my_shell->sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &my_shell->sa_sigint, NULL);
	sigaction(SIGQUIT, &my_shell->sa_sigquit, NULL);
}

void	set_signal_child(t_shell *my_shell)
{
	my_shell->sa_sigint.sa_handler = SIG_DFL;
	my_shell->sa_sigquit.sa_handler = SIG_DFL;
	my_shell->sa_sigint.sa_flags = 0;
	my_shell->sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &my_shell->sa_sigint, NULL);
	sigaction(SIGQUIT, &my_shell->sa_sigquit, NULL);
}

void	set_heredoc_signal(t_shell *my_shell)
{
	my_shell->sa_sigint.sa_handler = sig_herdoc_handler;
	my_shell->sa_sigquit.sa_handler = SIG_IGN;
	my_shell->sa_sigint.sa_flags = 0;
	my_shell->sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &my_shell->sa_sigint, NULL);
	sigaction(SIGQUIT, &my_shell->sa_sigquit, NULL);
}
