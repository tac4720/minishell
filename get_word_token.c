#include "minishell.h"

void quote_check(char *line, int *i)
{
    int quote;

    if (line && line[*i] && (line[*i] == '\'' || line[*i] == '\"'))
    {
        quote = line[*i];
        (*i)++;
        while (line[*i] && line[*i] != quote)
            (*i)++;
    }
}

void check_quotes(t_input *current, int *i)
{
    if (current->input[*i] == '\'' ){
        current->flag |= F_SQUOTES;
        (*i)++;
        while (current->input[*i] && current->input[*i] != '\'')
            (*i)++;
    }
    else if (current->input[*i] == '\"')
    {
        current->flag |= F_DQUOTES;
        (*i)++;
        while (current->input[*i] && current->input[*i] != '\"')
        {
			if (current->input[*i] && current->input[*i] == '$')
				current->flag |= F_MUL_DOLLAR;//名前変えたい、ダブルクォーテーション内のフラグを指している。これは
			(*i)++;
		}
    }
}
int check_flags(t_input *current)
{
    int i;

    i = 0;
    if (!current->input)
        return (0);
    current->flag = 0;
    while (current->input[i])
    {
        check_quotes(current, &i);
        if (current->input[i] == '$' && current->input[i] == '$')
            current->flag |= F_DOLLAR;
        if (current->input[i])
            i++;

    }
    if (ft_strchr(current->input, '='))
        current->flag |= F_ASSIGNMENT;
    return (current->flag);
}

t_input *get_word(char **s)
{
    t_input *cur;
    int n;

    n = 0;

    cur = ft_calloc(1, sizeof(t_input));
    //malloc失敗時の処理を書く
    while (*(*s + n) && !ft_strchr(OPERATORS, *(*s + n)) && !is_blank(*(*s + n)))
    {
        quote_check(*s, &n);
        if (*(*s + n))
            n++;

    }//この関数内でのクォートのあつかいびみょい
    cur->input = ft_substr(*s, 0, n);
    cur->flag = check_flags(cur);
	*s += n;
    return (cur);
}

t_token *get_word_token(char **s)
{
    t_input *cur;
    t_token *node;

    node = ft_calloc(1, sizeof(t_token));
    //malloc失敗時の処理を書く
    cur = get_word(s);
    if (cur->flag & F_DOLLAR || cur->flag & F_MUL_DOLLAR)
		node->type = ENV_PARAM;
    else
        node->type = WORD;
    node->cmd = cur;
    node->next = NULL;
    node->prev = NULL;

    return (node);
}