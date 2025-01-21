#include "minishell.h"

t_input *new_word_node(t_token **token_list)
{
    t_input *word;

    word = ft_calloc(sizeof(t_input));
    //mallocエラー処理
    if ((*token_list) && (*token_list)->cmd && (*token_list)->cmd->input)
        word->input = ft_strdup((*token_list)->cmd->input);
    else
        word->input = ft_strdup("");
    word->input = remove_quotes(word->input);//あとでかく
    word->flag = (*token_list)->cmd->flag;
    word->next = NULL;
    if (*token_list)
        *token_list = (*token_list)->next;
    return (word);
}
t_redir *new_redir_node(t_token **token_list)
{
    t_redir *node;

    node = ft_calloc(1, sizeof(t_redir));
    //mallocエラー処理
    node->type = (*token_list)->type;
    (*token_list) = (*token_list)->next;
    node->filename = new_word_node(token_list);
    // if (node->type == HEREDOC && g_stat != SIGINT)
	// 	parse_heredoc(shell, &node);heredocあとでかく
    return node;
}
t_redir *parse_redir(t_token **tok, t_redir **redir)
{
    t_redir *tmp;

    tmp = NULL;
    if (*redir)
        tmp = *redir;
    while ((*tok) && ((*tok)->type == HEREDOC \
	|| (*tok)->type == APPEND || (*tok)->type == FILE_IN \
	|| (*tok)->type == FILE_OUT))
    {
        if (*redir)
        {
            while ((*redir) && (*redir)->next)
                *redir = (*redir)->next;
            (*redir)->next = new_redir_node(tok);
            (*redir)->next->next = NULL;
            *redir = (*redir)->next;
        } 
        else
        {
            *redir = new_redir_node(tok);
            (*redir)->next = NULL;
            tmp = *redir;
        }
    }
    return (tmp);
}