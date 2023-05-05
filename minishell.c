/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:32:07 by kcw               #+#    #+#             */
/*   Updated: 2023/05/05 12:51:20 by dkham            ###   ########.fr       */
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
	char		**env;

	if (argc != 1)
		return (0);
	(void)argv;
	execute.env = copy_envp(envp);
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
	free_env(env);
	return (0);
}

char	**copy_envp(char **envp)
{
	int		count;
	int		i;
	char	**new_envp;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	new_envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
