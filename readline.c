#include "minishell.h"


static volatile sig_atomic_t g_sigint = 0; 

void init_environment(t_map *env, char **envp)
{
    char    *eq_pos;
    char    *name;
    char    *value;
    int     i;

    i = 0;
    while (envp[i])
    {
        eq_pos = ft_strchr(envp[i], '=');
        if (eq_pos)
        {
            name = ft_substr(envp[i], 0, eq_pos - envp[i]);
            value = ft_strdup(eq_pos + 1);
            if (!name || !value)
            {
                free(name);
                free(value);
                continue;
            }
            map_set(env, name, value);
            free(name);
            free(value);
        }
        i++;
    }
}

void	init_context(t_context *ctx, char **envp)
{
	ctx->shell_pgid = getpid();
	ctx->is_interactive = isatty(STDIN_FILENO);
	ctx->last_status = 0;
	ctx->environ = map_new();
	init_environment(ctx->environ, envp);
	// printf("%s\n", map_get(ctx->environ, "TEST"));
	tcgetattr(STDIN_FILENO, &ctx->shell_tmodes);
	setup_signals(ctx);
}


static void	initialize_shell(t_context **ctx, char **envp)
{
	*ctx = malloc(sizeof(t_context));
	if (!*ctx)
		exit(EXIT_FAILURE);
	init_context(*ctx, envp);
	setup_signals(*ctx);
}

static void	handle_sigint(t_context *ctx)
{
	if (g_sigint)
	{
		rl_redisplay();
		g_sigint = 0;
		ctx->last_status = 130;
	}
}

static void	process_input_line(char *input, t_context *ctx, char **envp)
{
	t_token		*tokens;
	t_ast_node	*ast;

	if (*input)
	{
		add_history(input);
		tokens = input_scanner(input);
		ast = parse_tokens(&tokens);
		if (ast)
		{
			expand_ast(ast, envp, ctx);
			execute_ast(ast, envp, ctx);
			// ctx->last_status = 0;
		}
		//free_tree(ast);的な関数を入れる
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_context	*ctx;
	char		*input;

	(void)argc;
	(void)argv;
	initialize_shell(&ctx, envp);
	// char test[] = "\"    hello world  \"";
	// remove_quotes(test);
	// printf("%s\n", test);
	while (1)
	{
		handle_sigint(ctx);
		input = readline("minishell:) ");
		if (!input)
			break ;
		process_input_line(input, ctx, envp);
		free(input);
	}
	return (ctx->last_status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_context	*ctx;
// 	char		*input;
// 	char *line;
// 	t_token *token;
// 	t_ast_node *tree;

// 	(void)argc;
// 	(void)argv;
// 	ctx = malloc(sizeof(t_context));
// 	init_context(ctx, envp);
// 	// ctx->last_status = 0;
// 	// ctx->environ = map_new();
// 	setup_signals(ctx);

// 	while (1)
// 	{
// 		if (g_sigint)
// 		{
// 			rl_redisplay();
// 			g_sigint = 0;
// 		}

// 		input = readline("minishell:)");

// 		if (input == NULL)
// 		{
// 			// printf("\nExiting...\n");
// 			break ;
// 		}
// 		if (*input)
// 		{
// 			add_history(input);
// 			token = input_scanner(input);
// 			tree = parse_tokens(&token);
// 			expand_ast(tree, envp, ctx);
// 			execute_ast(tree, envp, ctx);
// 			// print_ast(tree, 0);
// 			// interpret(input, &ctx); // 入力を解釈して実行
// 		}
// 		free(input);
// 	}
// 	return (0);
// }
