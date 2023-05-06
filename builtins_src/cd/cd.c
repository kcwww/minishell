/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:28 by dkham             #+#    #+#             */
/*   Updated: 2023/05/06 14:28:04 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(char **args, t_execute *execute)
{
	int		ret;
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (args[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 1);
			free(oldpwd);
			return ;
		}
	}
	else
		path = args[1];
	ret = chdir(path);
	if (ret < 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putendl_fd(": No such file or directory", 1);
		free(oldpwd);
		return ;
	}
	update_env_var(execute->env, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	update_env_var(execute->env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
}

void	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*found_env;
	t_env	*new_node;
	char	*key_value_pair;
	size_t	key_len;

	found_env = find_env_node(env, key);
	if (found_env)
	{
		free(found_env->value);
		found_env->value = ft_strdup(value);
	}
	else
	{
		key_len = ft_strlen(key);
		key_value_pair = (char *)malloc((key_len + ft_strlen(value) + 2) * sizeof(char));
		if (!key_value_pair)
			return ;
		ft_strlcpy(key_value_pair, key, key_len + 1);
		key_value_pair[key_len] = '=';
		ft_strlcpy(key_value_pair + key_len + 1, value, ft_strlen(value) + 1);
		new_node = create_new_env_node(key_value_pair);
		if (new_node)
			add_env_node(env, new_node);
		free(key_value_pair);
	}
}
