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

// void init_environment(t_map *env, char **envp)
// {
//     char    *eq_pos;
//     char    *name;
//     char    *value;
//     int     i;

//     i = 0;
//     while (envp[i])
//     {
//         eq_pos = ft_strchr(envp[i], '=');
//         if (eq_pos)
//         {
//             name = ft_substr(envp[i], 0, eq_pos - envp[i]);
//             value = ft_strdup(eq_pos + 1);
//             if (!name || !value)
//             {
//                 free(name);
//                 free(value);
//                 continue;
//             }
//             map_set(env, name, value);
//             free(name);
//             free(value);
//         }
//         i++;
//     }
// }

// void	init_context(t_context *ctx, char **envp)
// {
// 	ctx->shell_pgid = getpid();
// 	ctx->is_interactive = isatty(STDIN_FILENO);
// 	ctx->last_status = 0;
// 	ctx->environ = map_new();
// 	init_environment(ctx->environ, envp);
// 	tcgetattr(STDIN_FILENO, &ctx->shell_tmodes);
// 	setup_signals(ctx);
// }

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
		tokens = input_scanner(input, ctx);
		ast = parse_tokens(&tokens, ctx);
		if (ast)
		{
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
		handle_sigint(ctx);
		input = readline("minishell:) ");
		if (!input)
			break ;
		process_input_line(input, ctx, envp);
		free(input);
	}
	last = ctx->last_status;
	clean(ctx);
	return (last);
}
