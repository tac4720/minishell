#include "minishell.h"

static int check_pipe(char **s)
{
    (*s)++;
    if (**s != '|')
    {
        return (PIPE_OP);
    }
    return (ERROR);
}

int check_redir(char **s)
{
    if (**s == '<')
    {
        (*s)++;
        if (**s == '<')
        {
            (*s)++;
            return (HEREDOC);
        }
        return (FILE_IN);
    }
    else if (**s == '>')
    {
        (*s)++;
        if (**s == '>')
        {
            (*s)++;
            return (APPEND);
        }
        return (FILE_OUT);
    }
    return (ERROR);
}

void	operator_input(t_token *token)
{
	if (token->type == HEREDOC)
		token->str = ft_strdup("<<");
	else if (token->type == APPEND)
		token->str = ft_strdup(">>");
	else if (token->type == FILE_IN)
		token->str = ft_strdup("<");
	else if (token->type == FILE_OUT)
		token->str = ft_strdup(">");
	else if (token->type == PIPE_OP)
		token->str = ft_strdup("|");
	else if (token->type == ERROR)
		token->str = ft_strdup("&");//謎とりあえず書いてる感じがする
}

int get_op_type(char **s)
{
    if (**s == '|')
        return (check_pipe(s));
    else if (**s == '<')
		return (check_redir(s));
	else if (**s == '>')
		return (check_redir(s));
	return (ERROR);
    
}
t_token *get_operator_token(char **s, t_context *context)
{
    t_token *new_token;

    if (!s || !(*s))
        return (NULL);
    new_token = ft_calloc(1, sizeof(t_token));
    //mallocエラーしたときの挙動を書く
    if (new_token == NULL)
        malloc_error(context);
    //mallocエラーしたときの挙動を書く
    new_token->type = get_op_type(s);
    operator_input(new_token);
    new_token->flag = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
    return (new_token);
}
