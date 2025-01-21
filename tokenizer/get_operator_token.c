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

void	operator_input(t_token *node)
{
	if (node->type == HEREDOC)
		node->cmd->input = ft_strdup("<<");
	else if (node->type == APPEND)
		node->cmd->input = ft_strdup(">>");
	else if (node->type == FILE_IN)
		node->cmd->input = ft_strdup("<");
	else if (node->type == FILE_OUT)
		node->cmd->input = ft_strdup(">");
	else if (node->type == PIPE_OP)
		node->cmd->input = ft_strdup("|");
	else if (node->type == ERROR)
		node->cmd->input = ft_strdup("&");//謎とりあえず書いてる感じがする
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
t_token *get_operator_token(char **s)
{
    t_token *node;

    if (!s || !(*s))
        return (NULL);
    node = ft_calloc(1, sizeof(t_token));
    //mallocエラーしたときの挙動を書く
    node->cmd = ft_calloc(1, sizeof(t_input));//cmdという名前がきもいかも
    //mallocエラーしたときの挙動を書く
    node->type = get_op_type(s);
    operator_input(node);
    node->cmd->flag = 0;
    node->cmd->next = NULL;
	node->cmd->prev = NULL;
	node->next = NULL;
	node->prev = NULL;
    return (node);
}
