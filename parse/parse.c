#include "minishell.h"

t_ast_node  *parse_tokens(t_token **token_list, t_context *context)
{
    t_ast_node *tree;

    // context->root_node = tree;
    tree = NULL;
    if(token_list == NULL)
        return (NULL);
    tree = parse_pipeline(token_list, context);
    printf("パースが完了しました\n");
    return (tree);
}