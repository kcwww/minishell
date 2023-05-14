/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcw <kcw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/05/14 12:47:45 by kcw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

void	ft_shellclear(t_env **env)
{
	t_env	*start;

	if (env == 0 || *env == 0)
		return ;
	start = *env;
	while (start)
	{
		(*env) = (*env)->next;
		free(start->var);
		free(start->param);
		free(start->value);
		free(start);
		start = *env;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*get_line;
	t_shell	my_shell;

	atexit(check_leaks);
	if (argc != 1)
		return (0);
	(void)argv;
	init_shell(&my_shell, env);
	while (1)
	{
		get_line = readline("minishell $ ");
		if (get_line == NULL)
		{
			printf("exit\n");
			ft_shellclear(&my_shell.env);
			return (0);
		}
		add_history(get_line);
		if (check_quotation(get_line))
		{
			if (ft_strcmp("None", find_value(get_line, &my_shell)) != 0) //delete
				printf("%s\n", find_value(get_line, &my_shell)); //delete
			parsing_start(get_line, &my_shell);
		}
		free(get_line);
		free_all(&my_shell);
	}
}
