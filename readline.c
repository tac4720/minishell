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
			execute_ast(ast, envp, ctx);
			free_ast_tree(ast);
		}
	}
}

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
