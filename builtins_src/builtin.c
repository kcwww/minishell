/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/18 21:33:00 by dkham            ###   ########.fr       */
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
		handle_heredocs(cmd); // Handle here-docs and replace them with regular input redirections
		handle_redirections(cmd); // Handle other redirections
		if (!head->next && is_builtin(cmd->word[0])) // Handle builtin commands
			builtin(my_shell);
		else
		{	
			if (head->next && pipe(fd) < 0) // Handle pipes and forks
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
				child_process(my_shell, head, fd, cmd);
			else
				parent_process(head, fd);
		}
		head = head->next;
	}
	cleanup_heredocs(); // Clean up temporary here-doc files
}

void	handle_heredocs(t_shell *my_shell)
{
	t_pipes	*head;
	int		i;
	int		fd;
	char	*line;
// 이 함수는 my_shell->head를 순회하면서 각 command에 대해 '<<' redirection을 찾습니다. 
// 만약 찾는다면, 그 redirection을 처리하고, 그 결과를 임시 파일 "temp.txt"에 기록합니다. 
// 그 후, '<<' redirection을 '<'로 바꾸고, redirection 값으로 "temp.txt"를 사용합니다.
	head = my_shell->head;
	while (head)
	{
		i = 0;
		while (head->simple_cmd->redirection && head->simple_cmd->redirection[i])
		{
			if (ft_strcmp(head->simple_cmd->redirection[i], "<<") == 0)
			{
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
// 이 함수는 my_shell->head를 순회하면서 각 command에 대해 '<'나 '>' 리다이렉션을 찾습니다. 
// 만약 찾는다면, 그 리다이렉션을 처리하고, 그 결과를 my_shell의 fd_in 또는 fd_out에 저장합니다. 
// '<' 리다이렉션은 파일에서 읽어오는 역할을 하고, '>' 리다이렉션은 파일에 쓰는 역할을 합니다. 
// 이 결과를 my_shell의 fd_in 또는 fd_out에 저장하는 이유는, 이후에 이 파일 디스크립터를 사용해서 실제로 데이터를 읽거나 쓸 수 있도록 하기 위함입니다.
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

void	cleanup_heredocs(void)
{
	if (unlink("temp.txt") == -1)
	{
		perror("Failed to remove temporary file");
	}
}

void	child_process(t_shell *my_shell, t_pipes *head, int *fd, t_cmd *cmd)
{
// 이 두 조건은 프로세스의 입력이 표준 입력 (키보드)로부터 오는 것이 아니라 다른 곳 (파이프 또는 사용자 지정 파일)에서 오는 경우를 처리하기 위한 것입니다.

// 첫번째 if 조건은 프로세스의 입력이 파이프로부터 오는 경우를 처리합니다.
// 여기서 fd[0]는 이전 명령의 출력을 가져오는 파이프의 파일 디스크립터입니다.
// 만약 fd[0]가 표준 입력인 0이 아니라면 (fd[0] != 0), 입력이 파이프를 통해 오는 것이므로, 표준 입력을 fd[0]로 변경합니다. (dup2(fd[0], 0)).
// 예를 들어, "command1 | command2"라는 명령이 있다면, command2의 fd[0]는 command1의 출력을 가리킵니다.

// 두번째 else if 조건은 프로세스의 입력이 사용자가 지정한 파일이나 파일 디스크립터로부터 오는 경우를 처리합니다.
// 여기서 my_shell->fd_in은 사용자가 입력 리디렉션을 설정한 파일 디스크립터를 가리킵니다.
// 만약 my_shell->fd_in이 표준 입력인 0이 아니라면 (my_shell->fd_in != 0), 입력이 사용자가 지정한 파일이나 파일 디스크립터로부터 오는 것이므로, 표준 입력을 my_shell->fd_in로 변경합니다. (dup2(my_shell->fd_in, 0)). 
// 예를 들어, "command < file"라는 명령이 있다면, command의 my_shell->fd_in은 file을 가리킵니다.
	if (dup2(fd[0], 0) == -1)
		exit(EXIT_FAILURE);
	else if (my_shell->fd_in != 0)
	{
		if (dup2(my_shell->fd_in, 0) == -1)
			exit(EXIT_FAILURE);
	}
// 이 부분은 파이프의 출력(fd[1])을 현재 프로세스의 표준 출력(1)으로 리디렉션하는 역할을 합니다. 이는 파이프라인에서 이전 명령어의 출력을 다음 명령어의 입력으로 연결할 때 필요합니다. 
// 예를 들어 "command1 | command2"라는 명령어에서, command1의 출력이 command2의 입력으로 갈 때, 이 부분이 그 역할을 합니다.
// 위 부분은 my_shell 구조체에 저장된 fd_out을 표준 출력으로 리디렉션하는 역할을 합니다. 
// 이는 "command > file" 같은 명령에서 표준 출력을 파일로 리디렉션할 때 필요합니다. 여기서, my_shell->fd_out은 handle_redirections 함수에서 설정됩니다.
	if (dup2(fd[1], 1) == -1)
		exit(EXIT_FAILURE);
	else if (my_shell->fd_out != 1)
	{
		if (dup2(my_shell->fd_out, 1) == -1)
			exit(EXIT_FAILURE);
	}
// 내장된 명령어가 입력되었는지를 검사하고, 만약 그렇다면 해당 내장 명령어를 실행합니다. 그 후 프로세스를 성공적으로 종료합니다.
	if (is_builtin(cmd->word[0]))
	{
		builtin(my_shell);
		exit(EXIT_SUCCESS);
	}
// 입력받은 명령어가 내장 명령어가 아닌 경우를 처리합니다. 
// execve 함수는 새로운 프로그램을 실행하는 역할을 하는데, 이 때 첫 번째 인자는 실행할 프로그램의 경로, 두 번째 인자는 프로그램에 전달할 인자들의 배열, 세 번째 인자는 새로운 프로세스의 환경 변수를 담은 배열입니다.
// 이 부분에서는 새로운 프로그램의 경로로 cmd->word[0]를, 인자 배열로 cmd->word를 사용하고 있습니다. 이는 "ls -l" 같은 명령어를 처리할 때 "ls"가 프로그램 경로, "-l"이 인자가 되는 것입니다.
// 그리고 환경 변수 배열로는 NULL을 사용하고 있는데, 이는 현재 프로세스의 환경 변수를 그대로 상속받는 것을 의미합니다.
	else if (execve(cmd->word[0], cmd->word, NULL) == -1)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->word[0], 2);
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_pipes *head, int *fd)
{
	int	status;
	//이 함수는 파이프를 통해 데이터를 전송한 후에 필요없는 파이프를 닫고, 자식 프로세스가 종료될 때까지 대기하는 역할을 합니다.

	if (fd[0] != 0) // fd[0]가 표준 입력이 아니라면 (즉, 파이프나 파일 등 다른 소스에서 입력을 받는다면) fd[0]를 닫습니다.
		close(fd[0]);
	if (fd[1] != 1) // fd[1]이 표준 출력이 아니라면 (즉, 출력이 파이프나 파일 등 다른 곳으로 가는 경우) fd[1]을 닫습니다.
		close(fd[1]);
	while (wait(&status) > 0) // 부모 프로세스가 자식 프로세스가 종료될 때까지 기다리게 합니다. wait 함수는 자식 프로세스의 종료 상태를 받아오는 역할을 합니다.
	{
		if (WIFEXITED(status)) // 자식 프로세스가 어떻게 종료되었는지를 확인하고, 그에 따른 exit 상태를 전역 변수 g_exit_status에 저장합니다.
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status);
	}
}
