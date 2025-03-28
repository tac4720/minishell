/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:24:15 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/24 21:24:23 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unclosed_quote(char *line, t_context *ctx)
{
	ft_printf("unclosed_quote\n");
	clean(ctx);
	free(line);
	exit(1);
}

void	malloc_error(t_context *context)
{
	if (context->token_list_top)
		free_tokens(context->token_list_top);
	if (context->readline != NULL)
		free(context->readline);
	free(context);
	ft_printf("malloc error\n");
	exit(1);
}

void	error_in_parse(t_context *context)
{
	ft_printf("error in parse\n");
	if (context == NULL)
		exit(1);
	if (context->token_list_top != NULL)
		free_tokens(context->token_list_top);
	if (context->readline != NULL)
		free(context->readline);
	free_ast_tree(context->root_node);
	if (context->environ != NULL)
		free_map(context->environ);
	free(context);
	exit(1);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}
