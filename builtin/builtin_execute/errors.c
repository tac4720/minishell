/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:08:11 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/16 16:08:19 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_all_nodes_on_malloc_failure(t_context *context)
{
    // Free token list
    if (context->token_list_top != NULL)
        free_tokens(context->token_list_top);

    // Free readline buffer
    if (context->readline != NULL)
        free(context->readline);

    // Free context
    free(context);

    printf("malloc failure during parsing\n");
    exit(14); // Exit with a specific error code
}