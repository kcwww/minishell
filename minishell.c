/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/05/11 21:49:45 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_leaks(void)
// {
// 	system("leaks minishell");
// }

/*
	빌트인 함수는 부모에서 실행 (단, 파이프 있을 경우 자식에서 실행)
	일반 함수는 자식에서 실행 (ls 등)
	파이프 있을 때는 자식 열어주기
	
	히어독과 리다이렉션은 우선순위가 있다
	=> cat << a > 1 | cat << b > 2 | cat << c > 3 
	먼저 히어독을 처리하고 리다이렉션을 처리한다
	-> 임시 파일을 3개 만든다: 만약 b, c, a, b, c 입력 시 첫 임시 파일에는 b,c가 들어가고, 두 번째와 세번째 임시파일에는 들어가지 않는다
	-> <<를 <로 내부적으로 바꾸고, 인풋이 될 임시 파일 명을 지정해준다
	-> 이제 리다이렉션 처리를 수행한다
	   : < 가 있으면 인 리다이렉션을 수행: 인풋fd를 받는다
	   : > 가 있으면 아웃 리다이렉션을 수행: 아웃풋fd를 받는다
	-> 자식에서 실행:
		: if 인다이렉션이 있으면, 인풋fd를 받아서 인풋fd를 표준입력으로 바꾼다
		: else if 인다이렉이 없고, 파이프가 있으면, 파이프에서 읽는다
		: if 아웃리다이렉션이 있으면, 아웃풋fd를 받아서 아웃풋fd를 표준출력으로 바꾼다
		: else if 아웃리다이렉션이 없고, 파이프가 있으면, 파이프에 쓴다
		: 나머지는 stdout으로 출력한다 (ls 같은 경우 등)
*/

int	main(int argc, char **argv, char **envp)
{
	char		*get_line;
	t_execute	execute;

	//atexit(check_leaks);
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
		execute.args = ft_split(get_line, ' ');
		execute.fd_out = 1;
		builtin(&execute);
		free_2d_array(execute.args);
		add_history(get_line);
		free(get_line);
	}
	free_env_list(execute.env);
	return (0);
}

void	free_2d_array(char **array)
{
	char	**temp;

	temp = array;
	if (array == NULL)
		return ;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(array);
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
	new_node->next = NULL;
	return (new_node);
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

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}
