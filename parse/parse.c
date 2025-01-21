#include "minishell.h"

t_ast_node  *parse_line(t_token **token_list)
{
    t_ast_node *tree;

    tree = NULL;
    if(!token_list)
        return (NULL);
    tree = parse_pipeline(token_list);
    // return (parse_logic_op(tree, token_list));
    return (tree);
}