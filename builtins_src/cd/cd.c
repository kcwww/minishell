/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:28 by dkham             #+#    #+#             */
/*   Updated: 2023/05/27 12:59:07 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(t_shell *my_shell)
{
	char	*cur_pwd;
	char	**word;

	word = my_shell->head->simple_cmd->word;
	cur_pwd = getcwd(NULL, 0);
	if (cur_pwd == NULL)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", my_shell->fd_out);
		return ;
	}
	if (word[1] == NULL)
		handle_cd_no_word(my_shell, cur_pwd);
	else
		handle_cd_with_word(my_shell, word[1], cur_pwd);
}

void	handle_cd_no_word(t_shell *my_shell, char *cur_pwd)
{
	t_env	*home_env;

	home_env = find_env_node(my_shell->env, "HOME");
	if (home_env == NULL || home_env->value == NULL || \
	home_env->value[0] == '\0')
	{
		ft_putendl_fd("minishell: cd: HOME not set", my_shell->fd_out);
		free(cur_pwd);
		return ;
	}
	if (chdir(home_env->value) < 0)
	{
		ft_putstr_fd("minishell: cd: ", my_shell->fd_out);
		ft_putstr_fd(home_env->value, my_shell->fd_out);
		ft_putendl_fd(": No such file or directory", my_shell->fd_out);
	}
	else
	{
		update_env_var(my_shell->env, "OLDPWD", cur_pwd);
		update_env_var(my_shell->env, "PWD", getcwd(NULL, 0));
	}
	free(cur_pwd);
}

void	handle_cd_with_word(t_shell *my_shell, char *path, char *cur_pwd)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", my_shell->fd_out);
		ft_putstr_fd(path, my_shell->fd_out);
		ft_putendl_fd(": No such file or directory", my_shell->fd_out);
		free(cur_pwd);
		return ;
	}
	update_env_var(my_shell->env, "OLDPWD", cur_pwd);
	update_env_var(my_shell->env, "PWD", getcwd(NULL, 0));
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

t_env	*create_new_env_node(char *key_value_pair)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(key_value_pair, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		new_node->key = ft_strdup(key_value_pair);
		new_node->value = ft_strdup(equal_sign + 1);
		*equal_sign = '=';
	}
	else
	{
		new_node->key = ft_strdup(key_value_pair);
		new_node->value = ft_strdup("");
	}
	new_node->var = malloc(sizeof(char*) * 3);
	if (!new_node->var)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->var[0] = new_node->key;
	new_node->var[1] = new_node->value;
	new_node->var[2] = NULL;
	new_node->next = NULL;
	return (new_node);
}
