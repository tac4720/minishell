#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

// t_token *new_token(char *word)
// {
//     t_token *tok;

//     tok = calloc(1, sizeof(*tok));
//     if (tok == NULL)
//         return (0);//error内容を書く
//     tok->word = word;
//     // tok->kind = kind;
//     return (tok);
// }

int is_blank(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

t_token *get_token(char **s)
{
    if (!(*s))
        return (NULL);//空文字が渡されたとき、または文字列の読み込みが終わったとき
    while (**s && is_blank(**s))
    {
        (*s)++;
    }
    if (**s && ft_strchr(OPERATORS, **s))
        return (get_operator_token(s));
    else if (**s)
        return (get_word_token(s));
    return (NULL);
}

t_token *last_token(t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void token_add(t_token **token_list, t_token *token)
{
    t_token *tmp;
    t_token *last;

    if (*token_list == NULL)
    {
        *token_list = token;
        return;
    }
    else
    {
        last = last_token(*token_list);
        last->next = token;
        token->prev = last;
    }
    return;
}

t_token *input_scanner(char *line)
{
    t_token *token_list;
    t_token *token;

    token_list = NULL;
    token = NULL;
    while(*line)
    {
        token = get_token(&line);
        token_add(&token_list, token);
    }
    return (token_list);
}
