/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:36:14 by kcw               #+#    #+#             */
/*   Updated: 2023/05/03 21:44:19 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULITINS_H
# define BULITINS_H

typedef struct s_execute
{
	int		fd_in;
	int		fd_out;
	char	**env;
}	t_execute;

void	pwd(void);
void	echo(char **args, t_execute *execute);
void	builtin(char **args, t_execute *execute);
void	cd(char **args, t_execute *execute);
void	export(char **args, t_execute *execute);
void	unset(char **args, t_execute *execute);
void	env(t_execute *execute);
void	cmd_exit(char **args, t_execute *execute);
int		only_n_after_dash(const char *str);


#endif
