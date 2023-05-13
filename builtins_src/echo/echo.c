/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:09:50 by dkham             #+#    #+#             */
/*   Updated: 2023/05/13 10:35:36 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// echo $a option 구현해야 함

void	echo(t_execute *execute)
{
	int		i;
	int		n_flag;
	char	**word;

	word = execute->head->simple_cmd->word;
	i = 1;
	n_flag = handle_n_flag(word, &i);
	print_word(execute, i, n_flag);
}

int	handle_n_flag(char **word, int *i)
{
	int	n_flag;

	n_flag = 0;
	while (word[*i] && ft_strncmp(word[*i], "-n", 2) == 0)
	{
		if (only_n_after_dash(word[*i]))
		{
			n_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (n_flag);
}

int	only_n_after_dash(const char *str)
{
	int	j;

	j = 2;
	while (str[j])
	{
		if (str[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	print_word(t_execute *execute, int i, int n_flag)
{
	char	*env_var_val;
	char	**word;

	word = execute->head->simple_cmd->word;
	while (word[i])
	{
		env_var_val = get_env_var_value(execute, word[i]);
		if (env_var_val)
			ft_putstr_fd(env_var_val, execute->fd_out);
		else
			ft_putstr_fd(word[i], execute->fd_out);
		if (word[i + 1])
			ft_putstr_fd(" ", execute->fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", execute->fd_out);
}

char	*get_env_var_value(t_execute *execute, const char *str)
{
	char	*value;
	char	*key;
	t_env	*found_env;

	if (str[0] == '$')
	{
		key = ft_strdup(str + 1);
		found_env = find_env_node(execute->env, key);
		free(key);
		if (found_env && found_env->value)
			value = found_env->value;
		else
			value = NULL;
		return (value);
	}
	return (NULL);
}
