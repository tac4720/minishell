/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_redir_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:16:16 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/03/07 14:53:40 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_infile_redir_node(t_token **token_list, t_cmd *cmd,
int command_flag, t_context *context)
{
	cmd->infile_redir = ft_calloc(1, sizeof(t_infile_redir));
	if (cmd->infile_redir == NULL)
		error_in_parse(context);
	cmd->infile_redir->filename = ft_strdup((*token_list)->str);
	cmd->infile_redir->next = NULL;
	cmd->infile_redir->redirection_flag |= command_flag;
	*token_list = (*token_list)->next;
}

void	append_infile_redir_node(t_token **token_list, t_cmd *cmd,
int command_flag, t_context *context)
{
	t_infile_redir	*tmp;

	tmp = cmd->infile_redir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = ft_calloc(1, sizeof(t_infile_redir));
	if (tmp->next == NULL)
		error_in_parse(context);
	tmp->next->filename = ft_strdup((*token_list)->str);
	tmp->next->next = NULL;
	tmp->next->redirection_flag |= command_flag;
	*token_list = (*token_list)->next;
}

void	add_infile_redir_node(t_token **token_list, t_cmd *cmd,
int command_flag, t_context *context)
{
	if (cmd->infile_redir == NULL)
		create_infile_redir_node(token_list, cmd, command_flag, context);
	else
		append_infile_redir_node(token_list, cmd, command_flag, context);
	return ;
}
