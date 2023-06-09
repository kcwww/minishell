/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:29:49 by kcw               #+#    #+#             */
/*   Updated: 2023/06/09 21:25:14 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_tmp
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
}	t_tmp;

typedef struct s_num
{
	int	re_flag;
	int	re_num;
	int	re_word;
	int	word_num;
}	t_num;

int		check_quotation(char *str);
int		check_double(char *str, int i, char mark);
int		check_whitespace(char *str);
int		is_env(char c);
int		skip_spaces(char *str, int i);
void	free_three(char *tmp, char *tmp2, char *tmp3);
void	increase_num(t_num *num);
#endif
