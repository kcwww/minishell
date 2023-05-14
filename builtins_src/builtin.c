/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/14 11:21:06 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	빌트인 함수는 부모에서 실행 (단, 파이프 있을 경우 자식에서 실행)
	일반 함수는 자식에서 실행 (ls 등)
	파이프 있을 때는 자식 열어주기

	----------------------------------------------------
	히어독과 리다이렉션은 우선순위가 있다
	command << END > output.txt
	line1
	line2
	END
	-> END 나올때까지 입력 받은 후, 이를 command에 인풋으로 넣는다.
	-> command의 아웃풋을 output.txt에 넣는다
	----------------------------------------------------

	=> 예. cat << a > 1 | cat << b > 2 | cat << c > 3
	먼저 히어독을 처리하고 리다이렉션을 처리한다
	-> 임시 파일을 3개 만든다:
	-> 만약 apple, banana, a, b, c 입력 시
	첫 임시 파일에는 apple, banana가 들어가고, 두 번째와 세번째 임시파일에는 아무것도 들어가지 않는다
	-> <<를 <로 내부적으로 바꾸고, 인풋이 될 임시 파일 명을 지정해준다
	   => redirection 값: "<<" ">" --> "<" ">"
	   => redirection value 값: a --> temp.txt (감추기 필요? / 나중에 지우기 필요)
	-> 리다이렉션 처리를 수행한다
	   : < 가 있으면 인 리다이렉션을 수행: 인풋 fd를 받는다
	   : > 가 있으면 아웃 리다이렉션을 수행: 아웃풋 fd를 받는다
	-> 자식에서 실행:
		: if 인다이렉션이 있으면, 인풋fd를 받아서 인풋fd를 표준입력으로 바꾼다
		: else if 인다이렉이 없고, 파이프가 있으면, 파이프에서 읽는다
		: if 아웃리다이렉션이 있으면, 아웃풋fd를 받아서 아웃풋fd를 표준출력으로 바꾼다
		: else if 아웃리다이렉션이 없고, 파이프가 있으면, 파이프에 쓴다
		: 나머지는 stdout으로 출력한다 (ls 같은 경우 등)
*/

void	execute(t_shell *my_shell)
{
	t_pipes	*head;
	pid_t	pid;
	int		fd[2];
	t_cmd	*cmd;

	head = my_shell->head;
	while (head)
	{
		cmd = head->simple_cmd;
		if (!head->next && is_builtin(cmd->word[0]))  // 파이프가 없고 빌트인 명령어인 경우
			builtin(my_shell);  // 빌트인 명령어 바로 실행
		else
		{
			if (head->next && pipe(fd) < 0)  // 파이프가 있는 경우: 파이프 생성
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
				child_process(my_shell, head, fd, cmd);
			else  // 부모 프로세스
				parent_process(head, fd);
		}
		head = head->next;
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

void	builtin(t_shell *execute)
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

char	*check_access(t_shell *my_shell, char *cmd)
{
	int		i;
	char	*path;
	char	**paths;

	if (cmd[0] == '/')	// If the command is already an absolute path, return it directly.
	{
		if (access(cmd, F_OK) == 0) // if the file exists and is executable
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
		if (access(full_path_to_cmd, F_OK) == 0) // if the file exists and is executable, break the loop
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

char	**get_paths_from_env(t_env *env)
{
	char	*path_var;
	t_env	*current;
	int		path_count;
	int		i;

	path_var = NULL;
	current = env;
	while (current != NULL)	// Iterate through the linked list to find the PATH variable
	{
		if (ft_strncmp(current->key, "PATH", ft_strlen("PATH")) == 0)
		{
			path_var = current->value;
			break ;
		}
		current = current->next;
	}
	if (!path_var)	// If PATH variable is not found, return NULL
		return (NULL);
	path_count = count_paths(path_var); // Count the number of paths in the PATH variable
	char **paths = (char **)malloc(sizeof(char *) * (path_count + 1)); // +1 for the NULL at the end
	i = 0;
	while (i < path_count)
	{
		paths[i] = get_path(&path_var); 	// Get the separate paths
		i++;
	}
	paths[path_count] = NULL;
	return (paths); // Added parentheses in the return statement
}

// A helper function to count the number of segments separated by ':'
int	count_paths(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			count++;
		i++;
	}
	return (count + 1); // +1 for the extra path before the first :
}

// A helper function to get a single path segment
char	*get_path(char **str)
{
	char	*start;
	char	*path;

	start = *str;
	while (**str && **str != ':')
		(*str)++;
	path = ft_substr(start, 0, *str - start);
	if (**str)
		(*str)++; // Skip the ':' character
	return (path);
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

void	child_process(t_shell *my_shell, t_pipes *head, int fd[], t_cmd *cmd)
{
	char	*path_to_cmd;
	char	*temp;
	char	*err_msg;

		if (head->next)  // 다음 파이프가 있다면
		{
		close(fd[0]);  // 파이프의 읽기 끝을 닫습니다
		//dup2(fd[1], STDOUT_FILENO);  
		if (dup2(fd[1], STDOUT_FILENO) < 0) // 파이프의 쓰기 끝을 표준 출력에 복제합니다
			exit(EXIT_FAILURE);
		close(fd[1]);  // 원래의 쓰기 끝을 닫습니다
		}
		if (head != my_shell->head)  // 첫번째 파이프가 아니라면 (즉, 이전 파이프가 있다면)
		{
		//dup2(fd[0], STDIN_FILENO);  
		if (dup2(fd[0], STDIN_FILENO) < 0) // 이전 파이프의 읽기 끝을 표준 입력에 복제합니다
			exit(EXIT_FAILURE);
		close(fd[0]);  // 원래의 읽기 끝을 닫습니다
		close(fd[1]);  // 원래의 쓰기 끝을 닫습니다
		}
		handle_redirections(cmd);  // 리다이렉션을 처리합니다 (입력, 출력을 파일로 바꾸는 등)
		if (is_builtin(cmd->word[0]))  // 명령어가 빌트인 명령어인지 확인합니다 (echo, cd 등)
		builtin(my_shell);  // 빌트인 명령어라면 해당 함수를 실행합니다
		else  // 빌트인 명령어가 아니라면
		{
		path_to_cmd = check_access(my_shell, cmd->word[0]);  // 명령어에 해당하는 파일이 실행 가능한지 확인하고, 그 경로를 얻어옵니다
		if (path_to_cmd != NULL)  // 경로를 찾았다면
		{
			execve(path_to_cmd, cmd->word, NULL);  // 해당 경로의 프로그램을 실행합니다
			free(path_to_cmd);  // 경로 문자열 메모리를 해제합니다
			perror("execve error");  // execve 함수가 실패했다면 오류 메시지를 출력합니다
			exit(EXIT_FAILURE);  // 실패했으므로 프로세스를 종료합니다
		}
		else  // 명령어에 해당하는 파일을 찾지 못했다면
		{
			temp = ft_strjoin(cmd->word[0], ": command not found");  // 오류 메시지를 생성합니다
			err_msg = ft_strjoin("minishell: ", temp);  // 오류 메시지에 쉘 이름을 추가합니다
			ft_putendl_fd(err_msg, STDERR_FILENO);  // 오류 메시지를 표준 에러에 출력합니다
			free(temp);  // 메시지 문자열 메모리를 해제합니다
			free(err_msg);  // 메시지 문자열 메모리를 해제합니다
			exit(EXIT_FAILURE);
		}
	}
}

void	parent_process(t_pipes *head, int fd[])
{
	wait(NULL);
	if (head->next)
		close(fd[1]);
}
