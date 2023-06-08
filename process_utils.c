/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:19:37 by dkham             #+#    #+#             */
/*   Updated: 2023/06/08 22:17:53 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(char *full_path, char **word, char **env)
{
	if (word[0] != NULL && execve(full_path, word, env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	handle_external_command(t_shell *my_shell, t_pipes *head, char **env)
{
	char	*path_var;
	char	*full_path;

	if (ft_strlen(head->simple_cmd->word[0]) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	path_var = find_value("PATH", my_shell);
	full_path = check_access(path_var, head->simple_cmd->word[0]);
	if (full_path != NULL)
	{
		exec_command(full_path, head->simple_cmd->word, env);
		free(full_path);
	}
	else if (head->simple_cmd->word[0] != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(my_shell->head->simple_cmd->word[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
		exit(g_exit_status);
	}
}

char	*validate_and_construct_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*path_with_slash;
	int		i;

	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (full_path);
}

char	*check_access(char *path_var, char *cmd)
{
	char	**paths;
	char	*full_path;

	full_path = NULL;
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			full_path = ft_strdup(cmd);
	}
	else
	{
		if (path_var == NULL)
			return (NULL);
		paths = ft_split(path_var, ':');
		full_path = validate_and_construct_path(paths, cmd);
		free(paths);
	}
	return (full_path);
}
