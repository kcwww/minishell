/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/05/05 13:30:49 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	char		*get_line;
	char		**args;
	t_execute	execute;

	if (argc != 1)
		return (0);
	(void)argv;
	execute.env = copy_env_list(envp);
	while (1)
	{
		get_line = readline("minishell $ ");
		if (get_line == NULL)
		{
			error_str();
			return (0);
		}
		args = ft_split(get_line, ' ');
		execute.fd_out = 1;
		builtin(args, &execute);
		add_history(get_line);
		free(get_line);
	}
	free_env_list(execute.env);
	return (0);
}

t_env	*create_new_env_node(char *key_value_pair)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(key_value_pair, '=');
	*equal_sign = '\0';
	new_node->key = ft_strdup(key_value_pair);
	new_node->value = ft_strdup(equal_sign + 1);
	*equal_sign = '=';
	new_node->next = NULL;
	return (new_node);
}

t_env	*copy_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		if (head == NULL)
		{
			head = create_new_env_node(envp[i]);
			current = head;
		}
		else
		{
			current->next = create_new_env_node(envp[i]);
			current = current->next;
		}
		i++;
	}
	return (head);
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
}
