/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:52 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 21:04:47 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_heredoc(t_token **token_list, t_cmd *cmd,
int command_flags, t_context *context)
{
	*token_list = (*token_list)->next;
	if ((*token_list) == NULL)
	{
		ft_printf("syntax error heredoc\n");
		error_in_parse(context);
	}
	if ((*token_list)->type == WORD || (*token_list)->type == ENV_PARAM)
	{
		add_infile_redir_node(token_list, cmd, command_flags, context);
	}
	else
	{
		ft_printf("syntax error heredoc\n");
		error_in_parse(context);
	}
}

void	parse_file_in(t_token **token_list, t_cmd *cmd,
int command_flags, t_context *context)
{
	*token_list = (*token_list)->next;
	if ((*token_list) == NULL)
	{
		ft_printf("syntax error redirection\n");
		error_in_parse(context);
	}
	if ((*token_list)->type == WORD || (*token_list)->type == ENV_PARAM)
	{
		add_infile_redir_node(token_list, cmd, command_flags, context);
	}
	else
	{
		ft_printf("syntax error redirection\n");
		error_in_parse(context);
	}
}

void	parse_file_out(t_token **token_list, t_cmd *cmd,
int command_flags, t_context *context)
{
	*token_list = (*token_list)->next;
	if ((*token_list) == NULL)
	{
		ft_printf("syntax error redirection\n");
		error_in_parse(context);
	}
	if ((*token_list)->type == WORD || (*token_list)->type == ENV_PARAM)
	{
		add_outfile_redir_node(token_list, cmd, command_flags, context);
	}
	else
	{
		ft_printf("syntax error redirection\n");
		error_in_parse(context);
	}
}

void	parse_append(t_token **token_list, t_cmd *cmd,
int command_flags, t_context *context)
{
	*token_list = (*token_list)->next;
	if ((*token_list) == NULL)
	{
		ft_printf("syntax error redirection\n");
		error_in_parse(context);
	}
	if ((*token_list)->type == WORD || (*token_list)->type == ENV_PARAM)
	{
		add_outfile_redir_node(token_list, cmd, command_flags, context);
	}
	else
	{
		ft_printf("syntax error redirection\n");
		error_in_parse(context);
	}
}

void	parse_redir(t_token **token_list, t_cmd *cmd, t_context *context)
{
	if ((*token_list)->type == HEREDOC)
	{
		parse_heredoc(token_list, cmd, F_HEREDOC, context);
		return ;
	}
	if ((*token_list)->type == APPEND)
	{
		parse_append(token_list, cmd, F_APPEND, context);
		return ;
	}
	if ((*token_list)->type == FILE_IN)
	{
		parse_file_in(token_list, cmd, F_INFILE, context);
		return ;
	}
	if ((*token_list)->type == FILE_OUT)
	{
		parse_file_out(token_list, cmd, F_OUTFILE, context);
		return ;
	}
}
