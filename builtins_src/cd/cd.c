/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:28 by dkham             #+#    #+#             */
/*   Updated: 2023/04/30 12:29:18 by dkham            ###   ########.fr       */
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

void	cd(char **args)
{
	char	*pwd;
	char	*oldpwd;
	char	*home;

	// initialize variables
	pwd = NULL;
	oldpwd = NULL;
	home = NULL;
	// get current working directory
	pwd = getcwd(NULL, 0);
	// get home directory
	home = getenv("HOME");
	// if no args, go to home directory
	if (!args[1])
	{
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return ;
		}
		chdir(home);
	}
	// if args[1] is "-", go to previous directory
	else if (ft_strcmp(args[1], "-") == 0)
	{
		// get old working directory
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return ;
		}
		chdir(oldpwd);
	}
	// else, go to the directory specified in args[1]
	else
	{
		if (chdir(args[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": ", 2);
			perror("");
		}
	}
	// update OLDPWD and PWD
	oldpwd = pwd;
	pwd = getcwd(NULL, 0);
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", pwd, 1);
	// free memory
	free(pwd);
}
