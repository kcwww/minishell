/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:36:14 by kcw               #+#    #+#             */
/*   Updated: 2023/05/05 17:32:14 by dkham            ###   ########.fr       */
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
	t_env	*env;
}	t_execute;

void	builtin(char **args, t_execute *execute);
void	pwd(void);
void	echo(char **args, t_execute *execute);
void	cd(char **args, t_execute *execute);
void	export(char **args, t_execute *execute);
void	unset(char **args, t_execute *execute);
void	env(t_execute *execute);
void	cmd_exit(char **args, t_execute *execute);

int		only_n_after_dash(const char *str);
char	*expand_env_var(const char *str);
void	print_args(char **args, int i, int n_flag, t_execute *execute);
int		handle_n_flag(char **args, int *i);
char	*get_parent_dir(void);
void	handle_special_cases(char **dir, char **last_dir);
t_env	*create_new_env_node(char *key_value_pair);
t_env	*copy_env_list(char **envp);
void	free_env_node(t_env *node);
void	free_env_list(t_env *env);
void	add_env_node(t_env *env, t_env *new_node);
void	print_env_list(t_env *env);
int		is_valid_identifier(char *arg);
void	process_argument(char *arg, t_execute *execute);


#endif
