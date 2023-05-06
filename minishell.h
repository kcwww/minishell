/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:57:05 by kcw               #+#    #+#             */
/*   Updated: 2023/05/06 13:25:54 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "include/parse.h"
# include "include/bulitins.h"
# include "include/redirections.h"
# include "include/error_shell.h"
# include "include/init.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char	**word;
	char	redirection;
}	t_cmd;

typedef struct s_pipes
{
	struct s_pipes	*next;
	struct s_cmd	simple_cmd;
}	t_pipes;

typedef struct s_env
{
	char			**var;
	char			*param;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	struct s_pipes	*head;
	struct s_env	*env;
}	t_shell;

void	init_shell(t_shell *my_shell, char **env);
char	*find_value(char *key, t_env *env);

#endif
