/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/27 13:35:41 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_fd(t_shell *my_shell)
{
	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	my_shell->pipe_fd[0] = 0;
	my_shell->pipe_fd[1] = 1;
	my_shell->prev_pipe_fd_0 = 0;
	my_shell->last_cmd_flag = 0;
	my_shell->heredoc_used = 0;
}

void	execute(t_shell *my_shell, char **env)
{
	t_pipes	*head;
	pid_t	pid;
	pid_t	exited_pid;
	int		status;
	int		i;

	i = 0;
	status = 0;
	head = my_shell->head;
	init_fd(my_shell);
	handle_heredocs(my_shell);
	while (head)
	{
		my_shell->fd_in = 0;
		my_shell->fd_out = 1;
		if (head->next == NULL)
			my_shell->last_cmd_flag = 1;
		i++;
		handle_redirections(my_shell, head);
		if (!head->next && is_builtin(head->simple_cmd->word[0]))
			builtin(my_shell);
		else
		{
			if (head->next && pipe(my_shell->pipe_fd) == -1)
				exit(EXIT_FAILURE);
			pid = fork();
			if (pid < 0)
				exit(EXIT_FAILURE);
			else if (pid == 0)
				child_process(my_shell, head, env, i);
			else
				parent_process(my_shell, i);
		}
		head = head->next;
	}
	if (my_shell->heredoc_used == 1)
		cleanup_heredocs(my_shell);
	while (i--)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (exited_pid == pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = WTERMSIG(status);
		}
	}
}

// void	handle_heredocs(t_shell *my_shell)
// {
// 	t_pipes	*head;
// 	int		i;
// 	int		fd;
// 	char	*line;
// 	char	*tmpfile;

// 	head = my_shell->head;
// 	while (head)
// 	{
// 		i = 0;
// 		while (head->simple_cmd->redirection && head->simple_cmd->redirection[i])
// 		{
// 			if (ft_strcmp(head->simple_cmd->redirection[i], "<<") == 0)
// 			{
// 				my_shell->heredoc_used = 1;
// 				tmpfile = ft_strjoin("/tmp/", head->simple_cmd->redir_value[i]);
// 				fd = open(tmpfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 				while (1)
// 				{
// 					line = readline("> ");
// 					if (ft_strcmp(line, head->simple_cmd->redir_value[i]) == 0)
// 					{
// 						free(line);
// 						break ;
// 					}
// 					ft_putendl_fd(line, fd);
// 					free(line);
// 				}
// 				free(head->simple_cmd->redirection[i]);
// 				head->simple_cmd->redirection[i] = ft_strdup("<");
// 				free(head->simple_cmd->redir_value[i]);
// 				head->simple_cmd->redir_value[i] = ft_strdup(tmpfile);
// 				close(fd);
// 			}
// 			i++;
// 		}
// 		head = head->next;
// 	}
// }
void	make_hd(t_shell *my_shell, char *filename, char *end_str)
{
	int		fd;
	char	*line;

	my_shell->heredoc_used = 1;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, end_str) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	handle_heredocs(t_shell *my_shell)
{
	t_pipes	*head;
	int		i;
	char	*tmpfile;

	head = my_shell->head;
	while (head)
	{
		i = 0;
		while (head->simple_cmd->redirection && \
		head->simple_cmd->redirection[i])
		{
			if (ft_strcmp(head->simple_cmd->redirection[i], "<<") == 0)
			{
				tmpfile = ft_strjoin("/tmp/", head->simple_cmd->redir_value[i]);
				make_hd(my_shell, tmpfile, head->simple_cmd->redir_value[i]);
				free(head->simple_cmd->redirection[i]);
				head->simple_cmd->redirection[i] = ft_strdup("<");
				free(head->simple_cmd->redir_value[i]);
				head->simple_cmd->redir_value[i] = ft_strdup(tmpfile);
			}
			i++;
		}
		head = head->next;
	}
}

void	handle_redirections(t_shell *my_shell, t_pipes	*head)
{
	int		i;
	int		fd;

	i = 0;
	while (head->simple_cmd->redirection[i])
	{
		if (ft_strcmp(head->simple_cmd->redirection[i], "<") == 0)
		{
			fd = open(head->simple_cmd->redir_value[i], O_RDONLY);
			if (fd < 0)
				ft_putstr_fd("No such file or directory\n", 2);
			my_shell->fd_in = fd;
		}
		else if (ft_strcmp(head->simple_cmd->redirection[i], ">") == 0)
		{
			fd = open(head->simple_cmd->redir_value[i], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				ft_putstr_fd("No such file or directory\n", 2);
			my_shell->fd_out = fd;
		}
		i++;
	}
	head = head->next;
	return ;
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	builtin(t_shell *my_shell)
{
	char	*cmd;

	cmd = my_shell->head->simple_cmd->word[0];
	if (ft_strcmp(cmd, "cd") == 0)
		cd(my_shell);
	else if (ft_strcmp(cmd, "echo") == 0)
		echo(my_shell);
	else if (ft_strcmp(cmd, "env") == 0)
		env(my_shell);
	else if (ft_strcmp(cmd, "exit") == 0)
		cmd_exit(my_shell);
	else if (ft_strcmp(cmd, "export") == 0)
		export(my_shell);
	else if (ft_strcmp(cmd, "pwd") == 0)
		pwd(my_shell);
	else if (ft_strcmp(cmd, "unset") == 0)
		unset(my_shell);
	else
	{
		ft_putstr_fd("Error: command not found\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	cleanup_heredocs(t_shell *my_shell)
{
	int	i;

	i = 0;
	while (my_shell->head)
	{
		if (my_shell->head->simple_cmd->redir_value[i])
		{
			if (ft_strncmp(my_shell->head->simple_cmd->redir_value[i], "/tmp/", 5) == 0)
				unlink(my_shell->head->simple_cmd->redir_value[i]);
		}
		my_shell->head = my_shell->head->next;
	}
}

/*
	if 인리다이렉션(<)이 있으면, my_shell->fd_in를 표준입력으로 바꾼다
	else if 인리다이렉션(<)이 없고, 파이프가 있으면, 파이프에서 읽는다
	if 아웃리다이렉션이 있으면, my_shell->fd_out을 표준출력으로 바꾼다
	else if 아웃리다이렉션이 없고, 파이프가 있으면, 파이프에 쓴다
	나머지는 표준출력으로 출력한다 (ls 같은 경우 등)
*/

void	child_process(t_shell *my_shell, t_pipes *head, char **env, int i)
{
	char	*path_var;
	char	*full_path;

	if (my_shell->fd_in != 0) // Input redirection handling
	{
		if (dup2(my_shell->fd_in, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(my_shell->fd_in);
	}
	else if (my_shell->pipe_fd[0] != 0 && i != 1) // If there is a pipe and no input redirection
	{
		if (dup2(my_shell->prev_pipe_fd_0, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (my_shell->fd_out != 1) // Output redirection handling
	{
		if (dup2(my_shell->fd_out, 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(my_shell->fd_out);
	}
	else if (my_shell->pipe_fd[1] != 1 && my_shell->last_cmd_flag != 1) // If there is a pipe and no output redirection
	{
		if (dup2(my_shell->pipe_fd[1], 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(my_shell->pipe_fd[1]);
	}
	if (my_shell->pipe_fd[0] != 0)
		close(my_shell->pipe_fd[0]);
	if (is_builtin(head->simple_cmd->word[0]))
	{
		builtin(my_shell); // handle the built-in function
		exit(0); // Assuming success
	}
	else
	{
		path_var = find_value("PATH", my_shell);
		full_path = check_access(path_var, head->simple_cmd->word[0]);
		if (full_path != NULL)
		{
			if (head->simple_cmd->word[0] != NULL && execve(full_path, head->simple_cmd->word, env) == -1)//if (head->simple_cmd->word[0] != NULL && execve(full_path, head->simple_cmd->word, env) == -1)
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
	exit(1);
}

char *get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);  // "PATH="를 건너뛰고 그 이후의 문자열을 반환합니다.
		i++;
	}
	return (NULL);  // PATH 환경 변수가 발견되지 않았을 경우 NULL을 반환합니다.
}

char *check_access(char *path_var, char *cmd)
{
    char **paths;
    char *full_path;
    int i;
    char *path_with_slash;

    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')) // 수정된 부분
    {
        if (access(cmd, F_OK) == 0)  // If file exists at this path
            return (ft_strdup(cmd));  // Return a copy of cmd as the full path
        else
            return (NULL);  // If file does not exist, return NULL
    }
    paths = ft_split(path_var, ':');
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
    free(paths);
    return (full_path);
}

void	parent_process(t_shell *my_shell, int i)
{
	if (my_shell->fd_in != 0) // fd_in이 표준 입력이 아니라면 (즉, 입력이 파이프나 파일 등 다른 곳으로부터 오는 경우) fd_in을 닫습니다.
		close(my_shell->fd_in);
	if (my_shell->fd_out != 1) // fd_out이 표준 출력이 아니라면 (즉, 출력이 파이프나 파일 등 다른 곳으로 전달되는 경우) fd_out을 닫습니다.
		close(my_shell->fd_out);
	//dup2(my_shell->pipe_fd[0], 0); // pipe의 read-side를 STDIN으로 복제 (포크 전에 미리 세팅)
	
	if (my_shell->pipe_fd[1] != 1)
		close(my_shell->pipe_fd[1]); // write-side를 닫음
	if (i != 1) // 첫 심플 커맨드인 경우 실행 안함
		close(my_shell->prev_pipe_fd_0); // 전 커맨드에서 안 닫고 살려둔 pipe_fd[0]을 닫아줌
	my_shell->prev_pipe_fd_0 = my_shell->pipe_fd[0]; // 파이프 리드 사이드 다음 루프 위해 저장
}
