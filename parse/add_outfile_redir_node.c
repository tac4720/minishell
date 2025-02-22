/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_outfile_redir_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:12:06 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 21:05:27 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_outfile_redir_node(t_token **token_list, t_cmd *cmd,
int command_flag, t_context *context)
{
	cmd->outfile_redir = ft_calloc(1, sizeof(t_outfile_redir));
	if (cmd->outfile_redir == NULL)
		error_in_parse(context);
	cmd->outfile_redir->filename = ft_strdup((*token_list)->str);
	cmd->outfile_redir->next = NULL;
	cmd->outfile_redir->redirection_flag |= command_flag;
	*token_list = (*token_list)->next;
}

void	append_outfile_redir_node(t_token **token_list, t_cmd *cmd,
int command_flag, t_context *context)
{
	t_outfile_redir	*tmp;

	tmp = cmd->outfile_redir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = ft_calloc(1, sizeof(t_outfile_redir));
	if (tmp->next == NULL)
		error_in_parse(context);
	tmp->next->filename = ft_strdup((*token_list)->str);
	tmp->next->next = NULL;
	cmd->outfile_redir->redirection_flag |= command_flag;
	*token_list = (*token_list)->next;
}

void	add_outfile_redir_node(t_token **token_list, t_cmd *cmd,
int command_flag, t_context *context)
{
	if (cmd->outfile_redir == NULL)
		create_outfile_redir_node(token_list, cmd, command_flag, context);
	else
		append_outfile_redir_node(token_list, cmd, command_flag, context);
	return ;
}
