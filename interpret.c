#include "minishell.h"



t_ast_node	*interpret(char *line, t_context *context)
{
	t_token *token_list;
    t_ast_node *tree;
	token_list = input_scanner(line);
	while(token_list)
    {
        printf("%s\n", token_list->cmd->input);
        token_list = token_list->next;
    }

    tree = parse_line(&token_list);
    return (tree);
}


