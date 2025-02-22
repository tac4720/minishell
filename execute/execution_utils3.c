/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:44:27 by tac               #+#    #+#             */
/*   Updated: 2025/02/18 21:16:58 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	info_set(t_ast_node *node, t_ast_node **cmds, t_exec_info *info,
	t_context *ctx)
{
	info->count = 0;
	info->envp = ctx->env;
	store_commands(node, cmds, &info->count);
	reverse_commands(cmds, info->count);
	info->i = 0;
}
