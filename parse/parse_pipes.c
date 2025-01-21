#include "minishell.h"

t_ast_node *parse_pipeline(t_token **token_list)
{
    t_ast_node *node;

    node = parse_cmd(token_list);
    return (parse_pipe(node, token_list));//parse_pipeという名前きもいって
}

t_ast_node *parse_pipe(t_ast_node *left, t_token **token_list)
{
    t_ast_node *node;
    t_pipe  *pipe_node;
    if (*token_list && (*token_list)->type == PIPE_OP)
    {
        node = ft_calloc(1, sizeof(t_ast_node));
        //mallocエラー処理
        pipe_node = ft_calloc(1, sizeof(t_pipe));
        //mallocエラー処理
        node->type = AST_PIPE;
        pipe_node->in_fd = -2;
        pipe_node->out_fd = -2;
        pipe_node->left = left;
        *token_list = (*token_list)->next;
        pipe_node->right = parse_cmd(token_list);
        node->node = (void *)pipe_node;
        // node->red_lst = NULL;
        node->in_fd = -2;
        node->out_fd = -2;
        return (parse_pipe(node, token_list));
    }
    return (left);
}