/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:55:14 by dkham             #+#    #+#             */
/*   Updated: 2023/06/04 12:42:20 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	builtin(t_shell *my_shell, t_pipes *head)
{
	char	*cmd;

	cmd = head->simple_cmd->word[0];
	if (ft_strcmp(cmd, "cd") == 0)
		cd(my_shell);
	else if (ft_strcmp(cmd, "echo") == 0)
		echo(my_shell, head);
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
		exit(1);
	}
}
