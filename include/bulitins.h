/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:36:14 by kcw               #+#    #+#             */
/*   Updated: 2023/05/13 12:30:56 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULITINS_H
# define BULITINS_H

// typedef struct s_pipes
// {
// 	struct s_pipes	*next;
// 	struct s_cmd	*simple_cmd; // pipe 기준 커맨드 덩어리 전체
// }	t_pipes;

// typedef struct s_cmd
// {
// //	인풋 cat << a > 1 | cat << b > 2 | cat << c > 3로 가정:
//     char	**word; // cat 들어감
// 	char	**redirection; // << > 들어감
// 	char  **redir_value; // a, 1 들어감
// }	t_cmd;

// typedef struct s_env
// {
// 	char			**var; // 환경변수 리스트 각 줄
// 	char			*key; // key
// 	char			*value; // value
// 	struct s_env	*next;
// }	t_env;

// typedef struct s_execute // 모든 것을 담고 있는 struct
// {
// 	int		fd_in;
// 	int		fd_out;
// 	t_pipes	*head; // 시작 주소
// 	t_env	*env; // 환경변수
// }	t_execute;

t_pipes	*create_head(void);
t_cmd	*create_simple_cmd(void);

void	builtin(t_execute *execute);
void	execute(t_execute *my_shell);
int		is_builtin(char *cmd);
void	handle_redirections(t_cmd *cmd);

void	pwd(void);

void	echo(t_execute *execute);
int		handle_n_flag(char **word, int *i);
int		only_n_after_dash(const char *str);
void	print_word(t_execute *execute, int i, int n_flag);
char	*get_env_var_value(t_execute *execute, const char *str);

void	cmd_exit(t_execute *execute);
char	*validate_exit_word(t_execute *execute, int *exit_code);

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
void	handle_cd_no_word(t_execute *execute, char *oldpwd);
void	handle_cd_with_word(t_execute *execute, char *path, char *oldpwd);
void	update_env_var(t_env *env, char *key, char *value);

void	free_2d_array(char **array);
t_env	*copy_env_list(char **envp);
t_env	*create_new_env_node(char *key_value_pair);
void	free_env_list(t_env *head);
void	free_env_node(t_env *node);

#endif
