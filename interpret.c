#include "minishell.h"

t_ast_node	*interpret(char *line, t_context *context)
{
	t_token *token_list;
    t_ast_node *tree;
	check_open_close(line);//クォーテーションで閉じられているか決める
	token_list = input_scanner(line);

	t_token *token_list_for_printf;
    token_list_for_printf = token_list;
	while(token_list_for_printf)
    {
        printf("token_list:%s,token_type:%d,token_flag:%d\n", token_list_for_printf->str, token_list_for_printf->type, token_list_for_printf->flag);

        token_list_for_printf = token_list_for_printf->next;
    }

    tree = parse_tokens(&token_list);

    t_command_args *command_args_for_printf;

    while(command_args_for_printf != NULL)
    {
        printf("%s\n", command_args_for_printf->string);
        command_args_for_printf = command_args_for_printf->next;
    }

	// // コマンドの引数チェック

    // //parsetest ls > testa > testb
    // ft_printf("%s\n", tree->command_node->command_args->string);
    // ft_printf("%s\n", tree->command_node->outfile_redir->filename);
    // ft_printf("%s\n", tree->command_node->outfile_redir->next->filename);

    // //parsetest ls < testa < testb
    // ft_printf("%s\n", tree->command_node->command_args->string);
    // ft_printf("%s\n", tree->command_node->infile_redir->filename);
    // ft_printf("%s\n", tree->command_node->infile_redir->next->filename);

    // ft_printf("%s\n", tree->command_node->command_args->string);

    // //pipetest ls <fe | few < ffdsa
    // ft_printf("%s\n", tree->pipe_node->left->command_node->command_args->string);
    // ft_printf("%s\n", tree->pipe_node->right->command_node->command_args->string);
    // ft_printf("%s\n", tree->pipe_node->left->command_node->infile_redir->filename);
    // ft_printf("%s\n", tree->pipe_node->left->command_node->outfile_redir->filename);
    // ft_printf("%s\n", tree->pipe_node->right->command_node->infile_redir->filename);

    // //test"> fef"
    // ft_printf("%s\n", tree->command_node->outfile_redir->filename);

    return (tree);
}

