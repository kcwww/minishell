/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/13 12:15:12 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	builtin(t_execute *execute)
// {
// 	if (ft_strncmp(execute->word[0], "echo", 5) == 0)
// 		echo(execute);
// 	else if (ft_strncmp(execute->word[0], "pwd", 4) == 0)
// 		pwd();
// 	else if (ft_strncmp(execute->word[0], "cd", 3) == 0)
// 		cd(execute);
// 	else if (ft_strncmp(execute->word[0], "export", 7) == 0)
// 		export(execute);
// 	else if (ft_strncmp(execute->word[0], "unset", 6) == 0)
// 		unset(execute);
// 	else if (ft_strncmp(execute->word[0], "env", 4) == 0)
// 		env(execute);
// 	else if (ft_strncmp(execute->word[0], "exit", 5) == 0)
// 		cmd_exit(execute);
// 	else
// 		ft_putendl_fd("minishell: command not found", 1);
// }

char	*check_access(t_execute *my_shell, char *cmd)
{
	int		i;
	char	*path;
	char	**paths;

	// If the command is already an absolute path, return it directly.
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0) // if the file exists and is executable
			return (ft_strdup(cmd));
		else
			return (NULL);
	}

	paths = get_paths_from_env(my_shell->env);
	i = 0;
	while (paths && paths[i]) // iterate through the path list to find the file
	{
		path = ft_strjoin(paths[i], "/"); // append slash
		char *full_path_to_cmd = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path_to_cmd, X_OK) == 0) // if the file exists and is executable, break the loop
		{
			free_2d_array(paths);
			return (full_path_to_cmd);
		}
		free(full_path_to_cmd);
		i++;
	}
	free_2d_array(paths);
	return (NULL);
}

// A helper function to count the number of segments separated by ':'
int count_paths(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == ':')
            count++;
    return count + 1; // +1 for the extra path before the first :
}

// A helper function to get a single path segment
char *get_path(char **str)
{
    char *start = *str;
    while (**str && **str != ':')
        (*str)++;
    char *path = ft_substr(start, 0, *str - start);
    if (**str)
        (*str)++; // Skip the ':' character
    return path;
}

char **get_paths_from_env(t_env *env)
{
	char *path_var = NULL;
	t_env *current = env;

	// Iterate through the linked list to find the PATH variable
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PATH", ft_strlen("PATH")) == 0)
		{
			path_var = current->value;
			break;
		}
		current = current->next;
	}

	// If PATH variable is not found, return NULL
	if (!path_var)
		return NULL;

	// Count the number of paths in the PATH variable
	int path_count = count_paths(path_var);

	// Allocate memory for the paths array
	char **paths = (char **)malloc(sizeof(char *) * (path_count + 1)); // +1 for the NULL at the end

	// Get the separate paths
	int i = 0;
	while (i < path_count)
	{
		paths[i] = get_path(&path_var);
		i++;
	}
	paths[path_count] = NULL;

	return (paths); // Added parentheses in the return statement
}

void	execute(t_execute *my_shell)
{
	t_pipes	*head;
	pid_t	pid;
	int		fd[2];
	t_cmd	*cmd;
	char	*path_to_cmd;

	head = my_shell->head;
	while (head)
	{
		cmd = head->simple_cmd;
		if (!head->next && is_builtin(cmd->word[0]))  // 파이프가 없고 빌트인 명령어인 경우
			builtin(my_shell);  // 빌트인 명령어 바로 실행
		else  // 파이프가 있거나 빌트인 명령어가 아닌 경우
		{
			if (head->next && pipe(fd) < 0)  // 파이프가 있는 경우 파이프 생성
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
			pid = fork();
			if (pid < 0)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)  // 자식 프로세스
			{
				if (head->next)  // 파이프 처리: 출력
				{
					close(fd[0]);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
				}
				if (head != my_shell->head)  // 파이프 처리: 입력
				{
					dup2(fd[0], STDIN_FILENO);
					close(fd[0]);
					close(fd[1]);
				}
				handle_redirections(cmd);  // 리다이렉션 처리
				if (is_builtin(cmd->word[0]))  // 빌트인 명령어인 경우
					builtin(my_shell);  // 빌트인 명령어 바로 실행
				else  // 빌트인 명령어가 아닌 경우
				{
					path_to_cmd = check_access(my_shell, cmd->word[0]);
					if (path_to_cmd != NULL)
					{
						execve(path_to_cmd, cmd->word, NULL);
						free(path_to_cmd);
						perror("execve error");
						exit(EXIT_FAILURE);
					}
					else
					{
						fprintf(stderr, "minishell: %s: command not found\n", cmd->word[0]);
						exit(EXIT_FAILURE);
					}
				}
			}
			else  // 부모 프로세스
			{
				wait(NULL);
				if (head->next)
					close(fd[1]);
			}
		}
		head = head->next;
	}
}

void	builtin(t_execute *execute)
{
	char	**word;

	word = execute->head->simple_cmd->word;
	if (ft_strncmp(word[0], "echo", 5) == 0)
		echo(execute);
	else if (ft_strncmp(word[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(word[0], "cd", 3) == 0)
		cd(execute);
	else if (ft_strncmp(word[0], "export", 7) == 0)
		export(execute);
	else if (ft_strncmp(word[0], "unset", 6) == 0)
		unset(execute);
	else if (ft_strncmp(word[0], "env", 4) == 0)
		env(execute);
	else if (ft_strncmp(word[0], "exit", 5) == 0)
		cmd_exit(execute);
	else
	{
		printf("minishell: command not found: %s\n", word[0]);
		exit(EXIT_FAILURE);
	}
}

int	is_builtin(char *cmd)
{
	char	*builtin_str[7];
	int		i;

	builtin_str[0] = "echo";
	builtin_str[1] = "pwd";
	builtin_str[2] = "cd";
	builtin_str[3] = "export";
	builtin_str[4] = "unset";
	builtin_str[5] = "env";
	builtin_str[6] = "exit";
	i = 0;
	while (i < 7)  // 빌트인 명령어의 수만큼 반복
	{
		if (ft_strncmp(cmd, builtin_str[i], ft_strlen(builtin_str[i]) + 1) == 0)
			return (1);  // 빌트인 명령어일 경우 1을 반환
		i++;
	}
	return (0);  // 빌트인 명령어가 아닐 경우 0을 반환
}

void	handle_redirections(t_cmd *cmd)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], "<", 2) == 0)
		{
			fd = open(cmd->redir_value[i], O_RDONLY, 0644); // 입력 리다이렉션
			if (fd < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (ft_strncmp(cmd->redirection[i], ">", 2) == 0)
		{
			fd = open(cmd->redir_value[i], O_WRONLY | O_CREAT | O_TRUNC, 0644); // 출력 리다이렉션
			if (fd < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(cmd->redirection[i], ">>", 3) == 0)
		{
			fd = open(cmd->redir_value[i], O_WRONLY | O_CREAT | O_APPEND, 0644); // 출력 리다이렉션 (추가 모드)
			if (fd < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(cmd->redirection[i], "<<", 3) == 0) // heredoc
		{
			fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // Open a temporary file for here-document redirection
			if (fd < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			while (1)
			{
				line = readline("> "); // Read the input
				if (strcmp(line, cmd->redir_value[i]) == 0) // If the limiter is found, break out of the loop
					break;
				write(fd, line, strlen(line)); // Write the input into the temporary file
				write(fd, "\n", 1); // Write a newline character
				free(line); // Don't forget to free the allocated memory
			}
			free(line); // Don't forget to free the allocated memory
			close(fd); // Close the temporary file
			fd = open("temp.txt", O_RDONLY, 0644); // Re-open the temporary file for reading
			if (fd < 0)
			{
				perror("open error");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (remove("temp.txt") != 0) // Delete the temporary file
			{
				perror("Error deleting temporary file");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
}
