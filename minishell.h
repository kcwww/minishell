/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:57:05 by kcw               #+#    #+#             */
/*   Updated: 2023/05/12 15:37:28 by chanwoki         ###   ########.fr       */
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
	char			**var; // 환경변수 리스트
	char			*param; // key
	char			*value; // value
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	struct s_pipes	*head; //
	struct s_env	*env; // 환경변수
}	t_shell;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

void	init_shell(t_shell *my_shell, char **env);
char	*find_value(char *key, t_env *env);
void	parsing_start(char *str, t_shell *my_shell);

#endif
