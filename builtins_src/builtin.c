/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/23 18:05:59 by dkham            ###   ########.fr       */
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
		: if 인리다이렉션(<)이 있으면, my_shell->fd_in를 표준입력으로 바꾼다
		: else if 인리다이렉션(<)이 없고, 파이프가 있으면, 파이프에서 읽는다
		: if 아웃리다이렉션이 있으면, my_shell->fd_out을 표준출력으로 바꾼다
		: else if 아웃리다이렉션이 없고, 파이프가 있으면, 파이프에 쓴다
		: 나머지는 표준출력으로 출력한다 (ls 같은 경우 등)
	
	=> 예. pwd > a
*/

void	init_fd(t_shell *my_shell)
{
	my_shell->fd_in = 0;
	my_shell->fd_out = 1;
	my_shell->pipe_fd[0] = 0;
	my_shell->pipe_fd[1] = 1;
	my_shell->prev_pipe_fd_0 = 0;
	my_shell->last_cmd_flag = 0;
}

void	execute(t_shell *my_shell, char **env)
{
	t_pipes	*head;
	pid_t	pid;
	pid_t	exited_pid;
	int		heredoc_used;
	int		status;
	int		i;

	i = 0;
	status = 0;
	heredoc_used = 0;
	head = my_shell->head;
	init_fd(my_shell);
	while (head)
	{
		if (head->next == NULL)
			my_shell->last_cmd_flag = 1;
		i++;
		handle_heredocs(my_shell, &heredoc_used); // Handle here-docs and replace them with regular input redirections
		handle_redirections(my_shell);
		if (!head->next && is_builtin(head->simple_cmd->word[0]))
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
				child_process(my_shell, head, env, i);
			else
				parent_process(my_shell, i);
		}
		head = head->next;
	}
	if (heredoc_used)
		cleanup_heredocs();
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
			i++;
		}
		head = head->next;
	}
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

	path_var = get_path(env);
	full_path = check_access(path_var, head->simple_cmd->word[0]);
	if (full_path != NULL)
	{
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
			if (dup2(my_shell->prev_pipe_fd_0, 0) == -1)//if (dup2(my_shell->pipe_fd[0], 0) == -1)
			{
				
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			//close(my_shell->pipe_fd[0]); // 항상 닫아야 하므로 밖으로 뺌
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
				ft_putendl_fd("hello", 2);
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(my_shell->pipe_fd[1]);
		}
		if (my_shell->pipe_fd[0] != 0)
			close(my_shell->pipe_fd[0]);
		if (execve(full_path, head->simple_cmd->word, env) == -1)
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

	/*
	ls -l | wc -l | cat 했다고 가정
	
	<ls -l 실행>
	다음에 파이프(| wc -l)가 있으므로, pipe() 함수 실행되어 pipe_fd[0],[1]이 3, 4로 바뀜
	그리고 나서 fork 하면 부모/자식 각각 3,4/3,4가 열려있는 꼴이 됨
	
	자식은 써주는 일을 하므로 3번 리드 사이드는 읽어올 필요가 없어 닫아줌 (close(my_shell->pipe_fd[0]);)
	자식에서 4번 라이트 사이드는 dup2 후 execve 하면 자동으로 닫힘

	부모에서 라이트 사이드 4번은 부모에서 써줄 일이 없으므로 닫아줌 (close(my_shell->pipe_fd[1]);)
	부모에서 리드 사이드인 3은 이후 다음 세대 자식에서 읽어올 때 필요하므로 부모에서 닫지 않고 변수 만들어 저장
	(-> 그 다음 루프에서 닫아야 함)
	=> 부모: 3 / 자식: 다 닫힘 
	
	<wc -l 실행>
	3은 부모에서 닫지 않아 열려있음
	다음에 파이프(| cat)가 있으므로, pipe() 함수 실행되어 pipe_fd[0],[1]이 5, 6으로 바뀜
	fork 하면 부모는 (3) 5,6 / 자식 (3) 5, 6 (괄호 안 숫자는 열린 상태 의미)
	자식에서 첫 simple_cmd 아니면 dup2로 3에서 인풋 받아옴. 5는 닫음
	dup2 execve로 6에 쓰고 자동으로 닫힌다.

	부모는 라이트 사이드 6을 닫아준다.
	5번은 다음을 위해서 남긴다.
	부모에서 3번은 두번째 루프부터 무조건 닫는다.
	=> 부모: 5 / 자식: 다 닫힘.
	
	<cat 실행>
	자식은 5에서 dup2로 받아옴. execve 하면 기본이 stdout으로 출력
	부모는 5를 닫아줌
	
	
	*/
}
