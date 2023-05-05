/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:28 by dkham             #+#    #+#             */
/*   Updated: 2023/05/05 12:47:48 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// cd: with only a relative or absolute path

// external functions:
// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs

// void	cd(char **args, t_execute *execute)
// {
// 	char	*pwd;
// 	char	*oldpwd;

// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 	{
// 		perror("minishell: cd: error");
// 		return ;
// 	}
// 	oldpwd = ft_strdup(pwd);
// 	free(pwd);
// 	if (args[1] == NULL)
// 	{
// 		pwd = getenv("HOME");
// 		if (!pwd)
// 		{
// 			perror("minishell: cd: error");
// 			return ;
// 		}
// 	}
// 	else if (args[1][0] == '~')
// 	{
// 		pwd = ft_strjoin(getenv("HOME"), args[1] + 1);
// 		if (!pwd)
// 		{
// 			perror("minishell: cd: error");
// 			return ;
// 		}
// 	}
// 	else
// 		pwd = ft_strdup(args[1]);
// 	if (chdir(pwd) == -1)
// 	{
// 		perror("minishell: cd: error");
// 		free(pwd);
// 		return ;
// 	}
// 	free(pwd);
// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 	{
// 		perror("minishell: cd: error");
// 		return ;
// 	}
// 	set_env("OLDPWD", oldpwd, execute);
// 	set_env("PWD", pwd, execute);
// 	free(pwd);
// 	free(oldpwd);
// }

// // set_env function
// void	set_env(char *name, char *value, t_execute *execute)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (execute->env[i])
// 	{
// 		if (ft_strncmp(execute->env[i], name, ft_strlen(name)) == 0)
// 		{
// 			tmp = ft_strjoin(name, "=");
// 			free(execute->env[i]);
// 			execute->env[i] = ft_strjoin(tmp, value);
// 			free(tmp);
// 			return ;
// 		}
// 		i++;
// 	}
// 	tmp = ft_strjoin(name, "=");
// 	execute->env[i] = ft_strjoin(tmp, value);
// 	free(tmp);
// 	execute->env[i + 1] = NULL;
// }
