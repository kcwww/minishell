/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwoki <chanwoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:55:41 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/05 17:07:08 by chanwoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(char const *str, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != 0)
	{
		while (str[i] != 0 && str[i] == c)
			i++;
		if (str[i] != 0)
			cnt++;
		while (str[i] != 0 && str[i] != c)
			i++;
	}
	return (cnt);
}

int	check_word_len(char const *str, size_t i, char c)
{
	size_t	len;

	len = i;
	while (str[i] != 0 && str[i] != c)
		i++;
	return (i - len);
}

char	*word_input(char const *str, size_t str_i, char c)
{
	char	*word;
	size_t	word_len;
	size_t	i;

	word_len = check_word_len(str, str_i, c);
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (word == 0)
		return (0);
	word[word_len] = 0;
	i = 0;
	while (i < word_len)
	{
		word[i] = str[str_i];
		i++;
		str_i++;
	}
	return (word);
}

int	do_split(char **split, size_t split_len, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < split_len)
	{
		while (s[i] != 0 && s[i] == c)
			i++;
		if (s[i] != 0)
		{
			split[j] = word_input(s, i, c);
			if (split[j] == 0)
			{
				while (j-- > 0)
					free(split[j]);
				free(split);
				return (0);
			}
			j++;
		}
		while (s[i] != 0 && s[i] != c)
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	split_len;

	split_len = count_word(s, c);
	split = (char **)malloc(sizeof(char *) * (split_len + 1));
	if (split == 0)
		return (0);
	split[split_len] = 0;
	if (do_split(split, split_len, s, c) == 0)
		return (0);
	return (split);
}
