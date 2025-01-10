#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
typedef enum {
    TK_WORD,
    TK_EOF,
} TokenKind;

typedef struct s_token t_token;

struct s_token {
    char    *word;
    TokenKind kind;
    t_token *next;
};

t_token *new_token(char *word)
{
    t_token *tok;

    tok = calloc(1, sizeof(*tok));
    if (tok == NULL)
        return (0);//error内容を書く
    tok->word = word;
    // tok->kind = kind;
    return (tok);
}

bool is_blank(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

t_token *tokenize(char *line)
{
    int i = 0;
    int word_len = 0;
    int start_pos = 0;
    char *word;
    t_token *head = NULL;
    t_token *current_token = NULL;

    while(line[i])
    {
        if (!(is_blank(line[i])))
        {
            while(line[i] && !(is_blank(line[i])))
            {
                i++;
                word_len++;
            }
            word = strndup(&line[start_pos], word_len);
            if (word == NULL)
                return (NULL);
            if (current_token == NULL)
            {
                current_token = new_token(word);
                head = current_token;
            }
            else    
            {
                current_token->next = new_token(word);
                current_token = current_token->next;
            }
            word_len = 0;
        }
        i++;
        start_pos = i;
        
    }
    return (head);
}

int main()
{
    char *line = "lsss -ls    unyo";
    t_token *tok = tokenize(line);
    while(tok)
    {
        printf("%s\n", tok->word);
        tok = tok->next;
    }
    return (0);
}