/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:57 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 20:16:16 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_tokens(t_token **token_list, t_context *context)
{
	t_ast_node	*tree;

	tree = NULL;
	if (token_list == NULL)
		return (NULL);
	tree = parse_pipeline(token_list, context);
	return (tree);
}
