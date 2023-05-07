/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:28 by dkham             #+#    #+#             */
/*   Updated: 2023/05/07 12:55:07 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(t_execute *execute)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", 1);
		return ;
	}
	if (execute->args[1] == NULL)
		handle_cd_no_args(execute, oldpwd);
	else
		handle_cd_with_args(execute, execute->args[1], oldpwd);
}

void	handle_cd_no_args(t_execute *execute, char *oldpwd)
{
	t_env	*home_env;

	home_env = find_env_node(execute->env, "HOME");
	if (home_env == NULL || home_env->value == NULL || \
	home_env->value[0] == '\0')
	{
		ft_putendl_fd("minishell: cd: HOME not set", 1);
		free(oldpwd);
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
		update_env_var(execute->env, "OLDPWD", oldpwd);
		update_env_var(execute->env, "PWD", getcwd(NULL, 0));
	}
	free(oldpwd);
}

void	handle_cd_with_args(t_execute *execute, char *path, char *oldpwd)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putendl_fd(": No such file or directory", 1);
		free(oldpwd);
		return ;
	}
	update_env_var(execute->env, "OLDPWD", oldpwd);
	update_env_var(execute->env, "PWD", getcwd(NULL, 0));
	free(oldpwd);
}

void	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*found_env;

	found_env = find_env_node(env, key);
	if (found_env)
	{
		free(found_env->value);
		found_env->value = ft_strdup(value);
	}
	else
	{
		create_and_add_new_env_node(env, key, value);
	}
}

t_env	*create_and_add_new_env_node(t_env *env, char *key, char *value)
{
	t_env	*new_node;
	char	*key_value_pair;
	size_t	key_len;

	key_len = ft_strlen(key);
	key_value_pair = malloc((key_len + ft_strlen(value) + 2) * sizeof(char));
	if (!key_value_pair)
		return (NULL);
	ft_strlcpy(key_value_pair, key, key_len + 1);
	key_value_pair[key_len] = '=';
	ft_strlcpy(key_value_pair + key_len + 1, value, ft_strlen(value) + 1);
	new_node = create_new_env_node(key_value_pair);
	if (new_node)
		add_env_node(env, new_node);
	free(key_value_pair);
	return (new_node);
}
