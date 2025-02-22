/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:43 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 21:01:02 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_pipeline(t_token **token_list, t_context *context)
{
	t_ast_node	*node;

	node = NULL;
	if ((*token_list) == NULL)
	{
		ft_printf("syntax error\n");
		error_in_parse(context);
	}
	if ((*token_list)->type == PIPE_OP)
	{
		ft_printf("syntax error\n");
		error_in_parse(context);
	}
	context->root_node = node;
	node = parse_cmd(token_list, context);
	return (parse_pipe(node, token_list, context));
}

t_ast_node	*parse_pipe(t_ast_node *left, t_token **token_list,
t_context *context)
{
	t_ast_node	*new_node;

	if (*token_list != NULL)
	{
		if ((*token_list)->type == PIPE_OP)
		{
			new_node = ft_calloc(1, sizeof(t_ast_node));
			if (new_node == NULL)
				error_in_parse(context);
			context->root_node = new_node;
			new_node->pipe_node = ft_calloc(1, sizeof(t_pipe));
			if (new_node == NULL)
				error_in_parse(context);
			new_node->type = AST_PIPE;
			new_node->pipe_node->left = left;
			*token_list = (*token_list)->next;
			new_node->pipe_node->right = parse_cmd(token_list, context);
			return (parse_pipe(new_node, token_list, context));
		}
	}
	return (left);
}
