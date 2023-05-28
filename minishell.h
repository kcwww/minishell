/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:46:16 by dkham             #+#    #+#             */
/*   Updated: 2023/05/28 16:46:18 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "include/parse.h"
# include "include/redirections.h"
# include "include/error_shell.h"
# include "include/init.h"
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# define REDIRECTION 123
# define WORD 234
# define PIPE 456

typedef struct s_cmd
{ // cat << a > 1
	char	**word; 		// "cat"
	char	**redirection;	// "<<", ">"
	char	**redir_value;	// "a", "1"
}	t_cmd;

typedef struct s_pipes
{
	struct s_pipes	*next;
	struct s_cmd	*simple_cmd;
}	t_pipes;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
	int				prev_pipe_fd_0;
	int				last_cmd_flag;
	int				heredoc_used;
	int				error;
	char			*line;
	struct s_pipes	*head;
	struct s_env	*env;
}	t_shell;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

int		g_exit_status;

void	init_shell(t_shell *my_shell, char **env);
char	*find_value(char *key, t_shell *ms);
void	parsing_start(char *str, t_shell *my_shell);
void	make_simple_command(t_token *token, t_shell *my_shell);
void	free_all(t_shell *ms);
t_env	*create_new_env_node(char *key_value_pair);

void	cd(t_shell *execute);
void	handle_cd_no_word(t_shell *execute, char *oldpwd);
void	handle_cd_with_word(t_shell *execute, char *path, char *oldpwd);
void	update_env_var(t_env *env, char *key, char *value);

void	echo(t_shell *execute);
int		handle_n_flag(char **word, int *i);
int		only_n_after_dash(const char *str);
void	print_word(t_shell *execute, int i, int n_flag);
char	*get_env_var_value(t_shell *execute, char *str);

void	env(t_shell *execute);

void	cmd_exit(t_shell *execute);
char	*validate_exit_word(t_shell *execute, int *exit_code);

void	export(t_shell *execute);
void	print_env_list(t_env *env, t_shell *my_shell);
void	process_argument(char *arg, t_shell *execute);
int		is_valid_identifier(char *arg);
t_env	*sort_env_list(t_env *env);
int		cmp_env_nodes(t_env *tmp1, t_env *tmp2);
void	swap_env_nodes(t_env *tmp1, t_env *tmp2);
void	handle_argument_with_equals(char *arg, t_shell *execute);
void	handle_argument_without_equals(char *arg, t_shell *execute);
t_env	*find_env_node(t_env *env, char *key);
void	add_env_node(t_env *env, t_env *new_node);
void	free_env_node(t_env *node);

void	pwd(t_shell *my_shell);

void	unset(t_shell *execute);
void	remove_env_node(char *key, t_env **env);

void	init_fd(t_shell *my_shell);
void	execute(t_shell *my_shell, char **env);
pid_t	handle_proc(t_shell *my_shell, t_pipes *head, char **env, int i);
void	wait_for_children(int i, pid_t pid);

void	handle_heredocs(t_shell *my_shell);
void	make_hd(t_shell *my_shell, char *filename, char *end_str);
void	cleanup_heredocs(t_shell *my_shell);
void	handle_redirections(t_shell *my_shell, t_pipes	*head);
void	print_error_message(char *value);

void	handle_io_redirection(t_shell *my_shell, int i);
void	handle_external_command(t_shell *my_shell, t_pipes *head, char **env);
void	child_process(t_shell *my_shell, t_pipes *head, char **env, int i);
char	*validate_and_construct_path(char **paths, char *cmd);
char	*check_access(char *path_var, char *cmd);
void	parent_process(t_shell *my_shell, int i);

int		is_builtin(char *cmd);
void	builtin(t_shell *my_shell);



void	free_env(t_env *env);

#endif
