/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/05/13 10:39:29 by dkham            ###   ########.fr       */
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

void	execute(t_execute *my_shell)
{
	t_pipes *head;
	pid_t pid;
	int fd[2];
	t_cmd *cmd;

	head = my_shell->head;
	while (head)
	{
		cmd = head->simple_cmd;

		if (!head->next && is_builtin(cmd->word[0]))  // 파이프가 없고 빌트인 명령어인 경우
		{
			builtin(my_shell);  // 빌트인 명령어 바로 실행
		}
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
					execve(cmd->word[0], cmd->word, NULL);
					perror("execve error");
					exit(EXIT_FAILURE);
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
	int	i;
	int	fd;

	i = 0;
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], "<", 2) == 0)
		{
			fd = open(cmd->redir_value[i], O_RDONLY); // 입력 리다이렉션
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
		// 여기서 "<<" 히어 도큐먼트 리다이렉션을 처리하려면 추가적인 로직이 필요합니다.
		// 일반적으로 임시 파일을 생성하고 거기에 입력을 받은 뒤, 그 파일을 표준 입력으로 리다이렉트합니다.
		i++;
	}
}
