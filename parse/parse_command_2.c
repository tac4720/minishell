/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:13:10 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/03/01 22:14:00 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_args(t_token **token_list, t_cmd *cmd, t_context *context)
{
	t_command_args	*tmp;

	tmp = cmd->command_args;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = ft_calloc(1, sizeof(t_command_args));
	if (tmp->next == NULL)
		parse_args_failed(cmd, context);
	tmp->next->string = ft_strdup((*token_list)->str);
	if (tmp->next->string == NULL)
		parse_args_failed(cmd, context);
	tmp->next->next = NULL;
	tmp->next->flag = (*token_list)->flag;
}

void	parse_args(t_token **token_list, t_cmd *cmd, t_context *context)
{
	if (cmd->command_args == NULL)
	{
		cmd->command_args = ft_calloc(1, sizeof(t_command_args));
		if (cmd->command_args == NULL)
			parse_args_failed(cmd, context);
		cmd->command_args->string = ft_strdup((*token_list)->str);
		if (cmd->command_args->string == NULL)
			parse_args_failed(cmd, context);
		cmd->command_args->next = NULL;
		cmd->command_args->flag = (*token_list)->flag;
	}
	else
	{
		add_cmd_args(token_list, cmd, context);
	}
	*token_list = (*token_list)->next;
}
