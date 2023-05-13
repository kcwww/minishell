/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:28 by dkham             #+#    #+#             */
/*   Updated: 2023/05/12 17:54:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(t_execute *execute)
{
	char	*cur_pwd;
	char	**word;

	word = execute->head->simple_cmd->word;
	cur_pwd = getcwd(NULL, 0);
	if (cur_pwd == NULL)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", 1);
		return ;
	}
	if (word[1] == NULL)
		handle_cd_no_word(execute, cur_pwd);
	else
		handle_cd_with_word(execute, word[1], cur_pwd);
}

void	handle_cd_no_word(t_execute *execute, char *cur_pwd)
{
	t_env	*home_env;

	home_env = find_env_node(execute->env, "HOME");
	if (home_env == NULL || home_env->value == NULL || \
	home_env->value[0] == '\0')
	{
		ft_putendl_fd("minishell: cd: HOME not set", 1);
		free(cur_pwd);
		return ;
	}
	if (chdir(home_env->value) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(home_env->value, 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	else
	{
		update_env_var(execute->env, "OLDPWD", cur_pwd);
		update_env_var(execute->env, "PWD", getcwd(NULL, 0));
	}
	free(cur_pwd);
}

void	handle_cd_with_word(t_execute *execute, char *path, char *cur_pwd)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putendl_fd(": No such file or directory", 1);
		free(cur_pwd);
		return ;
	}
	update_env_var(execute->env, "OLDPWD", cur_pwd);
	update_env_var(execute->env, "PWD", getcwd(NULL, 0));
	free(cur_pwd);
}

void	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*found_env;
	size_t	key_len;
	char	*key_val_pair;
	t_env	*new_node;

	found_env = find_env_node(env, key);
	if (found_env)
	{
		free(found_env->value);
		found_env->value = ft_strdup(value);
	}
	else
	{
		key_len = ft_strlen(key);
		key_val_pair = malloc((key_len + ft_strlen(value) + 2) * sizeof(char));
		if (!key_val_pair)
			return ;
		ft_strlcpy(key_val_pair, key, key_len + 1);
		key_val_pair[key_len] = '=';
		ft_strlcpy(key_val_pair + key_len + 1, value, ft_strlen(value) + 1);
		new_node = create_new_env_node(key_val_pair);
		if (new_node)
			add_env_node(env, new_node);
		free(key_val_pair);
	}
}
