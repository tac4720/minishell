/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_in_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:37:27 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/16 13:02:30 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_command_args(t_command_args *args)
{
    t_command_args *tmp;
    while (args != NULL)
    {
        tmp = args->next;
        free(args->string);
        free(args);
        args = tmp;
    }
}

void free_redir_list(t_infile_redir *in_redir, t_outfile_redir *out_redir)
{
    t_infile_redir *tmp_in;
    t_outfile_redir *tmp_out;
    
    while (in_redir != NULL)
    {
        tmp_in = in_redir->next;
        free(in_redir->filename);
        free(in_redir);
        in_redir = tmp_in;
    }
    while (out_redir != NULL)
    {
        tmp_out = out_redir->next;
        free(out_redir->filename);
        free(out_redir);
        out_redir = tmp_out;
    }
}

void free_cmd_node(t_cmd *cmd)
{
    if (cmd == NULL)
        return;
    free_command_args(cmd->command_args);
    free_redir_list(cmd->infile_redir, cmd->outfile_redir);
    free(cmd);
}

void free_ast_tree(t_ast_node *node)
{
    if (node != NULL)
        return;
    
    if (node->type == AST_PIPE && (node->pipe_node != NULL))
    {
        free_ast_tree(node->pipe_node->left);
        free_ast_tree(node->pipe_node->right);
        free(node->pipe_node);
    }
    else if (node->type == AST_COMMAND && node->command_node)
    {
        free_cmd_node(node->command_node);
    }
    
    free(node);
}
