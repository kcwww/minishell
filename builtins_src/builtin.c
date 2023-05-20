/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/20 19:05:01 by dkham            ###   ########.fr       */
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
	
	=> 예. pwd > a
	
*/

void	execute(t_shell *my_shell, char **env)
{
	t_pipes	*head;
	pid_t	pid;
	t_cmd	*cmd;
	int		heredoc_used;

// 1. struct에서 fd_in, fd_out을 따로 저장하지 말고, int pipe_fd[2] 자체를 저장하자
// 그리고 pipe(pipe_fd)를 넣어주자.
// 그리고 pipe_fd[0]을 fd_in, pipe_fd[1]을 fd_out으로 사용하자
// 이후 parent와 child에도 pipe_fd를 넘겨주자

// 2. pwd 고쳐주었듯이 다른 빌트인도 고쳐주자(입출력 부분 fd_in, fd_out으로 바꾸기)

	heredoc_used = 0;
	my_shell->pipe_fd[0] = 0;
	my_shell->pipe_fd[1] = 0;
	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	head = my_shell->head;
	while (head)
	{
		cmd = head->simple_cmd;
		handle_heredocs(my_shell, &heredoc_used); // Handle here-docs and replace them with regular input redirections
		handle_redirections(my_shell); // Handle other redirections
		printf("haha\n");
		if (!head->next && is_builtin(cmd->word[0])) // Handle builtin commands
			builtin(my_shell);
		else
		{
			if (head->next && pipe(my_shell->pipe_fd) == -1)
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
			else if (pid == 0)
				child_process(my_shell, env);
			else
				parent_process(my_shell);
		}
		head = head->next;
	}
	if (heredoc_used)
		cleanup_heredocs(); // Clean up temporary here-doc files only if heredoc was used
}

void	handle_heredocs(t_shell *my_shell, int *heredoc_used)
{
	t_pipes	*head;
	int		i;
	int		fd;
	char	*line;

/*
	프로그램의 구조체인 my_shell에서 head를 얻어와 각 head의 simple_cmd에 있는 redirection을 확인합니다. 
	각 redirection이 here-document(<<)를 나타내는지 확인합니다. 
	만약 맞다면, temp.txt 파일을 생성하거나 열어서 그 내용을 지우고 (O_CREAT | O_RDWR | O_TRUNC), 사용자의 입력을 받아 파일에 작성합니다.

	이를 위해 readline() 함수를 사용하여 사용자의 입력을 받습니다. 
	사용자의 입력이 redir_value[i]과 같다면, 즉 here-document가 끝나는 표시를 만나면, 입력을 중단하고 루프를 탈출합니다. 
	그렇지 않다면, 사용자의 입력을 temp.txt에 작성하고 메모리를 해제합니다.

	그런 다음 현재의 redirection을 <로 변경하고, redir_value를 temp.txt로 변경합니다. 
	이는 이제 커맨드가 temp.txt를 읽어서 입력으로 사용하도록 하는 일반적인 입력 리디렉션을 나타냅니다. 
	이렇게 변경하고 난 후에 fd를 닫아서 파일을 사용 완료하고 메모리를 해제합니다.

	마지막으로 i를 증가시켜 다음 리디렉션을 검사하고, head를 다음 노드로 이동시킵니다. 
	이는 my_shell의 모든 파이프 라인에 대해 이 프로세스를 반복하게 합니다.
*/
	head = my_shell->head;
	while (head)
	{
		i = 0;
		while (head->simple_cmd->redirection && head->simple_cmd->redirection[i])
		{
			if (ft_strcmp(head->simple_cmd->redirection[i], "<<") == 0)
			{
				*heredoc_used = 1;
				fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
				while (1)
				{
					line = readline("> ");
					if (ft_strcmp(line, head->simple_cmd->redir_value[i]) == 0)
					{
						printf("line: %s\n", line);
						printf("redir_value: %s\n", head->simple_cmd->redir_value[i]);
						free(line);
						break ;
					}
					ft_putendl_fd(line, fd);
					free(line);
				}
				free(head->simple_cmd->redirection[i]);
				head->simple_cmd->redirection[i] = ft_strdup("<");
				free(head->simple_cmd->redir_value[i]);
				head->simple_cmd->redir_value[i] = ft_strdup("temp.txt");
				close(fd);
			}
			printf("i : %d\n", i);
			printf("redir : %s\n", head->simple_cmd->redirection[i]);
			i++;
		}
		printf("hello\n");
		head = head->next;
		// printf("%s\n", head->simple_cmd->word[0]);
	}
	printf("break\n");
}

void	handle_redirections(t_shell *my_shell)
{
	int		i;
	int		fd;
	t_pipes	*head;
	t_cmd	*cmd;
/*
	함수는 구조체 my_shell에서 head를 얻어와 각 head의 simple_cmd에 있는 redirection을 확인합니다. 각 redirection에 대해서 다음과 같이 처리합니다.

	입력 리디렉션(<) : redir_value[i]에서 파일 이름을 얻어옵니다. 이 파일을 읽기 모드(O_RDONLY)로 엽니다. 
	파일을 열지 못하면 오류 메시지를 출력하고 프로그램을 종료합니다.
	파일을 성공적으로 열면, my_shell->fd_in을 이 파일 디스크립터로 설정합니다. 이로써 커맨드가 이 파일에서 입력을 읽을 수 있게 됩니다.

	출력 리디렉션(>) : redir_value[i]에서 파일 이름을 얻어옵니다. 이 파일을 쓰기 모드(O_WRONLY)로 열고, 파일이 존재하지 않으면 생성(O_CREAT)하고, 파일이 이미 존재하면 내용을 지웁니다(O_TRUNC). 
	파일을 열지 못하면 오류 메시지를 출력하고 프로그램을 종료합니다.
	파일을 성공적으로 열면, my_shell->fd_out을 이 파일 디스크립터로 설정합니다. 이로써 커맨드가 출력을 이 파일에 쓸 수 있게 됩니다.

	마지막으로 i를 증가시켜 다음 리디렉션을 검사하고, head를 다음 노드로 이동시킵니다. 
	이는 my_shell의 모든 파이프 라인에 대해 이 프로세스를 반복하게 합니다.

	이 함수는 입력/출력 리디렉션을 성공적으로 설정하면 반환하며, 설정에 실패하면 프로그램을 종료합니다.
*/
	head = my_shell->head;
	while (head)
	{
		cmd = head->simple_cmd;
		i = 0;
		while (cmd->redirection[i])
		{
			if (ft_strcmp(cmd->redirection[i], "<") == 0)
			{
				fd = open(cmd->redir_value[i], O_RDONLY);
				if (fd < 0)
				{
					ft_putstr_fd("Error opening file for reading\n", 2);
					exit(EXIT_FAILURE);
				}
				my_shell->fd_in = fd;
			}
			else if (ft_strcmp(cmd->redirection[i], ">") == 0)
			{
				fd = open(cmd->redir_value[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					ft_putstr_fd("Error opening file for writing\n", 2);
					exit(EXIT_FAILURE);
				}
				my_shell->fd_out = fd;
			}
			i++;
		}
		head = head->next;
	}
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

void	cleanup_heredocs(void)
{
	if (unlink("temp.txt") == -1)
	{
		perror("Failed to remove temporary file");
	}
}

void	child_process(t_shell *my_shell, char **env)
{
	char	*path_var;
	char	*full_path;

	path_var = get_path(env);
	full_path = check_access(path_var, my_shell->head->simple_cmd->word[0]);
	if (full_path != NULL)
	{
		if (dup2(my_shell->pipe_fd[0], 0) == -1 || dup2(my_shell->pipe_fd[1], 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (execve(full_path, my_shell->head->simple_cmd->word, env) == -1)
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
	char	**paths;
	char	*full_path;
	int		i;
	char	*path_with_slash;

	paths = ft_split(path_var, ':');
	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free(paths);
	return (full_path);
}

void	parent_process(t_shell *my_shell)
{
	int	status;
	//이 함수는 파이프를 통해 데이터를 전송한 후에 필요없는 파이프를 닫고, 자식 프로세스가 종료될 때까지 대기하는 역할을 합니다.

	if (my_shell->fd_in != 0) // fd_in이 표준 입력이 아니라면 (즉, 입력이 파이프나 파일 등 다른 곳으로부터 오는 경우) fd_in을 닫습니다.
		close(my_shell->fd_in);
	if (my_shell->fd_out != 1) // fd_out이 표준 출력이 아니라면 (즉, 출력이 파이프나 파일 등 다른 곳으로 전달되는 경우) fd_out을 닫습니다.
		close(my_shell->fd_out);
	while (wait(&status) > 0) // 부모 프로세스가 자식 프로세스가 종료될 때까지 기다리게 합니다. wait 함수는 자식 프로세스의 종료 상태를 받아오는 역할을 합니다.
	{
		if (WIFEXITED(status)) // 자식 프로세스가 어떻게 종료되었는지를 확인하고, 그에 따른 exit 상태를 전역 변수 g_exit_status에 저장합니다.
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status);
	}
}
