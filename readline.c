#include "minishell.h"


static volatile sig_atomic_t g_sigint = 0; 

int	main(int argc, char **argv, char **envp)
{
	t_context	*ctx;
	char		*input;
	char *line;
	t_token *token;
	t_ast_node *tree;

	(void)argc;
	(void)argv;
	ctx = malloc(sizeof(t_context));
	// init_context(&ctx, envp);
	ctx->last_status = 0;
	ctx->environ = map_new();
	setup_signals(ctx);

	while (1)
	{
		if (g_sigint)
		{
			rl_redisplay();
			g_sigint = 0;
		}

		input = readline("minishell:)");

		if (input == NULL)
		{
			// printf("\nExiting...\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			token = input_scanner(input);
			tree = parse_tokens(&token);
			expand_ast(tree, envp, ctx);
			execute_ast(tree, envp, ctx);
			// print_ast(tree, 0);
			// interpret(input, &ctx); // 入力を解釈して実行
		}
		free(input);
	}
	return (ctx->last_status);
}