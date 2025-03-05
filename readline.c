/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:36 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 12:07:36 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_sigint = 0;

static void	initialize_shell(t_context **ctx, char **envp)
{
	*ctx = ft_calloc(1, sizeof(t_context));
	if (!*ctx)
		exit(EXIT_FAILURE);
	init_context(*ctx, envp);
	setup_signals(*ctx);
}

static void	handle_sigint(t_context *ctx)
{
	if (g_sigint)
	{
		setup_signals(ctx);
		ctx->last_status = 130;
		g_sigint = 0;
	}
}


#include <stdio.h>
#include "define.h"

void print_command_args(t_command_args *args, int indent) {
    while (args) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("- Arg: %s\n", args->string);
        args = args->next;
    }
}

void print_redirections(t_infile_redir *in, t_outfile_redir *out, int indent) {
    while (in) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("- Infile: %s (flag: %d)\n", in->filename, in->redirection_flag);
        in = in->next;
    }
    while (out) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("- Outfile: %s (flag: %d)\n", out->filename, out->redirection_flag);
        out = out->next;
    }
}

void print_ast_node(t_ast_node *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    if (node->type == AST_COMMAND) {
        printf("Command Node:\n");
        print_command_args(node->command_node->command_args, indent + 1);
        print_redirections(node->command_node->infile_redir, node->command_node->outfile_redir, indent + 1);
    } else if (node->type == AST_PIPE) {
        printf("Pipe Node:\n");
        print_ast_node(node->pipe_node->left, indent + 1);
        print_ast_node(node->pipe_node->right, indent + 1);
    }
}

void print_ast(t_context *ctx) {
    if (!ctx || !ctx->root_node) {
        printf("Empty AST\n");
        return;
    }

    printf("Abstract Syntax Tree:\n");
    print_ast_node(ctx->root_node, 0);
}


void print_token(t_token *token)
{
    if (!token)
    {
        printf("トークンがNULLです\n");
        return;
    }

    printf("トークン情報:\n");
    printf("  種類: ");
    switch (token->type)
    {
        case HEREDOC:   printf("ヒアドキュメント\n"); break;
        case APPEND:    printf("追加\n"); break;
        case FILE_IN:   printf("入力ファイル\n"); break;
        case FILE_OUT:  printf("出力ファイル\n"); break;
        case ENV_PARAM: printf("環境変数\n"); break;
        case PIPE_OP:   printf("パイプ演算子\n"); break;
        case WORD:      printf("単語\n"); break;
        case ERROR:     printf("エラー\n"); break;
        default:        printf("不明\n");
    }
    printf("  フラグ: %d\n", token->flag);
    printf("  文字列: %s\n", token->str ? token->str : "NULL");
    printf("  次のトークン: %p\n", (void*)token->next);
    printf("  前のトークン: %p\n", (void*)token->prev);
}

void print_token_list(t_token *head)
{
    t_token *current = head;
    int count = 0;

    while (current)
    {
        printf("トークン %d:\n", count++);
        print_token(current);
        printf("\n");
        current = current->next;
    }
}

static void	process_input_line(char *input, t_context *ctx, char **envp)
{
	t_token		*tokens;
	t_ast_node	*ast;

	if (*input)
	{
		add_history(input);
		tokens = input_scanner(input, ctx);
		ctx->token_list_top = tokens;
		ctx->root_node = NULL;
		ast = parse_tokens(&tokens, ctx);
		free_tokens(ctx->token_list_top);
		if (ast)
		{
			ctx->root_node = ast;
			expand_ast(ast, envp, ctx);
			// print_ast(ctx);
			execute_ast(ast, envp, ctx);
			free_ast_tree(ast);
		}
	}
}
// int			i;//test
// 	i = 0;//test
// t_token		*token_list_for_printf;//test
// token_list_for_printf = tokens;//test
// while(token_list_for_printf)
// {
// printf("token_list:%s,token_type:%d,token_flag:%d\n",
// token_list_for_printf->str,
//token_list_for_printf->type, token_list_for_printf->flag);
// token_list_for_printf = token_list_for_printf->next;
// }

void	clean(t_context *ctx)
{
	free_map(ctx->environ);
	free(ctx);
}

int	main(int argc, char **argv, char **envp)
{
	t_context	*ctx;
	char		*input;
	int			last;

	(void)argc;
	(void)argv;
	initialize_shell(&ctx, envp);
	while (1)
	{
		setup_signals(ctx);
		input = readline("minishell:) ");
		if (!input)
			break ;
		handle_sigint(ctx);
		check_open_close(input, ctx);
		ctx->input = input;
		process_input_line(input, ctx, envp);
		free(input);
	}
	last = ctx->last_status;
	clean(ctx);
	ft_putstr_fd("exit\n", 2);
	return (last);
}
