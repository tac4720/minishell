#include "minishell.h"



t_ast_node	*interpret(char *line, t_context *context)
{
	t_token *token_list;
    t_ast_node *tree;
	check_open_close(line);//クォーテーションで閉じられているか決める
	token_list = input_scanner(line);
	while(token_list)
    {
        printf("%s\n", token_list->str);
        token_list = token_list->next;//セグフォの原因
    }

    //ここまではセグフォせずにうまくはしっている。

    tree = parse_tokens(&token_list);
    return (tree);
}


