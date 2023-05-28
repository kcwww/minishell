/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:18:33 by dkham             #+#    #+#             */
/*   Updated: 2023/05/28 12:09:18 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_io_redirection(t_shell *my_shell, int i)
{
	if (my_shell->fd_in != 0)
	{
		if (dup2(my_shell->fd_in, 0) == -1)
			exit(EXIT_FAILURE);
		close(my_shell->fd_in);
	}
	else if (my_shell->pipe_fd[0] != 0 && i != 1)
	{
		if (dup2(my_shell->prev_pipe_fd_0, 0) == -1)
			exit(EXIT_FAILURE);
	}
	if (my_shell->fd_out != 1)
	{
		if (dup2(my_shell->fd_out, 1) == -1)
			exit(EXIT_FAILURE);
		close(my_shell->fd_out);
	}
	else if (my_shell->pipe_fd[1] != 1 && my_shell->last_cmd_flag != 1)
	{
		if (dup2(my_shell->pipe_fd[1], 1) == -1)
			exit(EXIT_FAILURE);
		close(my_shell->pipe_fd[1]);
	}
	if (my_shell->pipe_fd[0] != 0)
		close(my_shell->pipe_fd[0]);
}

void	handle_external_command(t_shell *my_shell, t_pipes *head, char **env)
{
	char	*path_var;
	char	*full_path;

	path_var = find_value("PATH", my_shell);
	full_path = check_access(path_var, head->simple_cmd->word[0]);
	if (full_path != NULL)
	{
		if (head->simple_cmd->word[0] != NULL && \
		execve(full_path, head->simple_cmd->word, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(full_path);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(my_shell->head->simple_cmd->word[0], 2);
		exit(EXIT_FAILURE);
	}
}

void	child_process(t_shell *my_shell, t_pipes *head, char **env, int i)
{
	handle_io_redirection(my_shell, i);
	if (is_builtin(head->simple_cmd->word[0]))
	{
		builtin(my_shell);
		exit(0);
	}
	else
		handle_external_command(my_shell, head, env);
	exit(1);
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
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			full_path = ft_strdup(cmd);
	}
	else
	{
		paths = ft_split(path_var, ':');
		full_path = validate_and_construct_path(paths, cmd);
		free(paths);
	}
	return (full_path);
}

void	parent_process(t_shell *my_shell, int i)
{
	if (my_shell->fd_in != 0)
		close(my_shell->fd_in);
	if (my_shell->fd_out != 1)
		close(my_shell->fd_out);
	if (my_shell->pipe_fd[1] != 1)
		close(my_shell->pipe_fd[1]);
	if (i != 1)
		close(my_shell->prev_pipe_fd_0);
	my_shell->prev_pipe_fd_0 = my_shell->pipe_fd[0];
}
