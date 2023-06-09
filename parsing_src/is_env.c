/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:51:00 by chanwoki          #+#    #+#             */
/*   Updated: 2023/06/09 21:42:36 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env(char c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '$' || c == '?' || \
		c == '~' || c == '.' || c == ':' || c == '|' || c == ';' || c == '>' || \
		c == '<' || c == '&' || c == '(' || c == ')' || c == '{' || c == '}' || \
		c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || \
		c == '\0' || c == '`' || c == '*' || c == '=' || c == '[' || \
		c == ']' || c == ',' || c == '\\' || c == '%')
		return (0);
	return (1);
}
