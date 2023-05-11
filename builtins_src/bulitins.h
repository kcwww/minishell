/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:36:14 by kcw               #+#    #+#             */
/*   Updated: 2023/05/11 22:06:04 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULITINS_H
# define BULITINS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_execute
{
	int		fd_in;
	int		fd_out;
	char	**args;
	char	**redir;
	t_env	*env;
}	t_execute;

void	builtin(t_execute *execute);

void	pwd(void);

void	echo(t_execute *execute);
int		handle_n_flag(char **args, int *i);
int		only_n_after_dash(const char *str);
void	print_args(t_execute *execute, int i, int n_flag);
char	*get_env_var_value(t_execute *execute, const char *str);

void	cmd_exit(t_execute *execute);
char	*validate_exit_args(t_execute *execute, int *exit_code);

void	env(t_execute *execute);

void	export(t_execute *execute);
void	print_env_list(t_env *env);
void	process_argument(char *arg, t_execute *execute);
int		is_valid_identifier(char *arg);
t_env	*sort_env_list(t_env *env);
int		cmp_env_nodes(t_env *tmp1, t_env *tmp2);
void	swap_env_nodes(t_env *tmp1, t_env *tmp2);
void	handle_argument_with_equals(char *arg, t_execute *execute);
void	handle_argument_without_equals(char *arg, t_execute *execute);
t_env	*find_env_node(t_env *env, char *key);
void	add_env_node(t_env *env, t_env *new_node);

void	unset(t_execute *execute);
void	remove_env_node(char *key, t_env **env);

void	cd(t_execute *execute);
void	handle_cd_no_args(t_execute *execute, char *oldpwd);
void	handle_cd_with_args(t_execute *execute, char *path, char *oldpwd);
void	update_env_var(t_env *env, char *key, char *value);

void	free_2d_array(char **array);
t_env	*copy_env_list(char **envp);
t_env	*create_new_env_node(char *key_value_pair);
void	free_env_list(t_env *head);
void	free_env_node(t_env *node);

#endif
