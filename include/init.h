/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:10:12 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 23:16:58 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

void	sigint_handler(int signo);
char	**ft_envsplit(char *str);
int		ft_strcmp(char *s1, char *s2);
void	check_signum(int signo);
void	sig_herdoc_handler(int signum);

#endif
