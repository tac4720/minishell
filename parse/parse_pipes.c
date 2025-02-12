#include "../minishell.h"

t_ast_node *parse_pipeline(t_token **token_list)
{
    // printf("parse_pipeline activated\n");
    t_ast_node *node;

    node = parse_cmd(token_list);
    return (parse_pipe(node, token_list));//parse_pipeという名前きもいって
}

t_ast_node *parse_pipe(t_ast_node *left, t_token **token_list)
{
    // printf("parse_pipe activated\n");
    t_ast_node *new_node;
    // t_pipe  *pipe_node;
    
    if (*token_list != NULL)
    {
        if ((*token_list)->type == PIPE_OP)
        {
            new_node = ft_calloc(1, sizeof(t_ast_node));
            //mallocエラー処理
            new_node->pipe_node = ft_calloc(1, sizeof(t_pipe));
            //mallocエラー処理
            new_node->type = AST_PIPE;

            // printf("test\n");
            new_node->pipe_node->left = left;
            *token_list = (*token_list)->next;
            new_node->pipe_node->right = parse_cmd(token_list);
            return (parse_pipe(new_node, token_list));
        }
    }
    return (left);
}
