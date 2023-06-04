/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:10:12 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/04 13:36:57 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

void	init_signal();
void	set_parent_signal();
void	set_signal_child(void);
void	set_heredoc_signal();
void	sigint_handler(int signo);
char	**ft_envsplit(char *str);
int		ft_strcmp(char *s1, char *s2);
void	check_signum(int signo);

#endif
