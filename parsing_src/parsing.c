/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:58:57 by chanwoki          #+#    #+#             */
/*   Updated: 2023/05/14 13:04:18 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int add_word(t_token *token, char *str)
{
    int i;
    i = 0;
    if (str[0] == '|')
    {
        token->value = (char *)malloc(sizeof(char) * 2);
        if (token->value == 0)
            return (-1);
        token->value[0] = '|';
        token->value[1] = '\0';
        token->type = PIPE;
        return (1);
    }
    if (str[0] == '>')
    {
        if (str[1] == '>')
        {
            token->value = (char *)malloc(sizeof(char) * 3);
            if (token->value == 0)
                return (-1);
            token->value[0] = '>';
            token->value[1] = '>';
            token->value[2] = '\0';
            token->type = REDIRECTION;
            return (2);
        }
        else
        {
            token->value = (char *)malloc(sizeof(char) * 2);
            if (token->value == 0)
                return (-1);
            token->value[0] = '>';
            token->value[1] = '\0';
            token->type = REDIRECTION;
            return (1);
        }
    }
    if (str[0] == '<')
    {
        if (str[1] == '<')
        {
            token->value = (char *)malloc(sizeof(char) * 3);
            if (token->value == 0)
                return (-1);
            token->value[0] = '<';
            token->value[1] = '<';
            token->value[2] = '\0';
            token->type = REDIRECTION;
            return (2);
        }
        else
        {
            token->value = (char *)malloc(sizeof(char) * 2);
            if (token->value == 0)
                return (-1);
            token->value[0] = '<';
            token->value[1] = '\0';
            token->type = REDIRECTION;
            return (1);
        }
    }
    while (str[i])
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
                i++;
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
                i++;
        }
        if (str[i] == ' ')
            break ;
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
            break ;
        i++;
    }
    token->value = (char *)malloc(sizeof(char) * (i + 1));
    if (token->value == 0)
        return (-1);
    ft_strlcpy(token->value, str, i + 1);
    token->type = WORD;
    return (i);
}
void    tokenizer(char *str, t_shell *ms)
{
    t_token *token;
    t_token *start;
    char    *new_str;
    int     i;
    i = 0;
    token = (t_token *)malloc(sizeof(t_token));
    if (token == 0)
        return ;
    ft_memset(token, 0, sizeof(t_token));
    start = token;
    while (i < ft_strlen(str))
    {
        while (str[i] == ' ')
            i++;
        if (str[i] == '\0')
            break ;
        new_str = ft_substr(str, i, ft_strlen(str) - i);
        if (new_str == NULL)
            return ;
        i = i + add_word(token, new_str);
        free(new_str);
        while (str[i] == ' ')
            i++;
        if (str[i] == '\0')
            break ;
        token->next = (t_token *)malloc(sizeof(t_token));
        if (token->next == 0)
            return ;
        token = token->next;
        token->next = NULL;
    }
    // token = start;
    // while (token)
    // {
    //  printf("token.value: %s\n", token->value);
    //  token = token->next;
    // }
    // printf("tokenizer end\n\n\n");
    // usleep(1000000);
    make_simple_command(start, ms);
    
    while (start)
    {
        token = start->next;
        free(start->value);
        free(start);
        start = token;
    }
}
void    parsing_start(char *str, t_shell *ms)
{
    tokenizer(str, ms);
}