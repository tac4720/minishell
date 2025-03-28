/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:31 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 20:57:27 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(t_token **token_list, t_cmd *cmd, t_context *context)
{
	t_command_args	*tmp;

	if (cmd->command_args == NULL)
	{
		cmd->command_args = ft_calloc(1, sizeof(t_command_args));
		if (cmd->command_args == NULL)
			error_in_parse(context);
		cmd->command_args->string = ft_strdup((*token_list)->str);
		cmd->command_args->next = NULL;
		cmd->command_args->flag = (*token_list)->flag;
	}
	else
	{
		tmp = cmd->command_args;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_calloc(1, sizeof(t_command_args));
		if (tmp->next == NULL)
			error_in_parse(context);
		tmp->next->string = ft_strdup((*token_list)->str);
		tmp->next->next = NULL;
		tmp->next->flag = (*token_list)->flag;
	}
	*token_list = (*token_list)->next;
}

void	add_cmd_node(t_token **token_list, t_cmd *cmd, t_context *context)
{
	while ((*token_list) != NULL)
	{
		if ((*token_list)->type != PIPE_OP)
		{
			if ((*token_list)->type == HEREDOC
				|| (*token_list)->type == APPEND
				|| (*token_list)->type == FILE_IN
				|| (*token_list)->type == FILE_OUT)
			{
				parse_redir(token_list, cmd, context);
			}
			else
			{
				parse_args(token_list, cmd, context);
			}
		}
		else
		{
			break ;
		}
	}
}

t_ast_node	*new_cmd_node(t_cmd *cmd, t_token **token_list, t_context *context)
{
	t_ast_node	*new_node;
	char		*tmp;

	new_node = ft_calloc(1, sizeof(t_ast_node));
	if (new_node == NULL)
		error_in_parse(context);
	new_node->command_node = cmd;
	if (cmd->num_of_words == 1)
	{
		cmd->command_args = ft_calloc(1, sizeof(t_command_args));
		if (cmd->command_args == NULL)
			error_in_parse(context);
		tmp = ft_strdup((*token_list)->str);
		new_node->command_node->command_args->string = tmp;
		new_node->command_node->command_args->next = NULL;
		new_node->command_node->command_args->flag = (*token_list)->flag;
		*token_list = (*token_list)->next;
	}
	else
		add_cmd_node(token_list, cmd, context);
	new_node->type = AST_COMMAND;
	return (new_node);
}

int	word_count(t_token *token_list)
{
	int	n;

	n = 0;
	while (token_list && (token_list->type == WORD
			|| token_list->type == ENV_PARAM))
	{
		n++;
		token_list = token_list->next;
	}
	return (n);
}

t_ast_node	*parse_cmd(t_token **token_list, t_context *context)
{
	t_cmd	*cmd;

	if ((*token_list) == NULL)
	{
		ft_printf("syntax error\n");
		error_in_parse(context);
	}
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		error_in_parse(context);
	cmd->in_fd = -2;
	cmd->out_fd = -2;
	cmd->command_args = NULL;
	cmd->infile_redir = NULL;
	cmd->outfile_redir = NULL;
	return (new_cmd_node(cmd, token_list, context));
}
