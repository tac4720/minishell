/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_in_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:06:06 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/03/01 22:07:11 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args_failed(t_cmd *cmd, t_context *context)
{
	free_cmd_node(cmd);
	free(context->node_in_process);
	error_in_parse(context);
}

void	new_cmd_node_failed_1(t_context *context)
{
	free(context->node_in_process);
	error_in_parse(context);
}

void	new_cmd_node_failed_2(t_context *context)
{
	free_cmd_node(context->node_in_process->command_node);
	free(context->node_in_process);
	error_in_parse(context);
}
