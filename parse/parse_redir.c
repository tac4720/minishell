#include "minishell.h"

void add_infile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag, t_context *context)//outfile,infile,appendすべてに対応していない。
{
    t_infile_redir *tmp;

    if (cmd->infile_redir == NULL)
    {
        cmd->infile_redir = ft_calloc(1, sizeof(t_infile_redir));
        if (cmd->infile_redir == NULL)
            error_in_parse(context);
        cmd->infile_redir->filename = ft_strdup((*token_list)->str);
        cmd->infile_redir->next = NULL;
        cmd->infile_redir->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    else
    {
        tmp = cmd->infile_redir;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = ft_calloc(1, sizeof(t_infile_redir));
        if (tmp->next == NULL)
            error_in_parse(context);
        tmp->next->filename = ft_strdup((*token_list)->str);
        tmp->next->next = NULL;
        cmd->infile_redir->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    return ;
}

void add_outfile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag, t_context *context)//outfile,infile,appendすべてに対応していない。
{
    t_outfile_redir *tmp;

    if (cmd->outfile_redir == NULL)
    {
        cmd->outfile_redir = ft_calloc(1, sizeof(t_outfile_redir));
        if (cmd->outfile_redir == NULL)
            error_in_parse(context);
        cmd->outfile_redir->filename = ft_strdup((*token_list)->str);
        // ft_printf("test:%s\n", cmd->outfile_redir->filename);
        cmd->outfile_redir->next = NULL;
        cmd->outfile_redir->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    else
    {
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
    return ;
}

void parse_heredoc(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context)
{
    *token_list = (*token_list)->next;
    if ((*token_list) == NULL)
    {
        ft_printf("syntax error heredoc\n");
        exit(0);
    }
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_infile_redir_node(token_list, cmd, command_flags, context);
    }
    else
    {
        ft_printf("syntax error heredoc\n");
        exit(0);
    }
}



void parse_file_in(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context)
{
    *token_list = (*token_list)->next;
    if ((*token_list) == NULL)
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_infile_redir_node(token_list, cmd, command_flags, context);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}

void parse_file_out(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context)
{
    *token_list = (*token_list)->next;
    if ((*token_list) == NULL)
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_outfile_redir_node(token_list, cmd, command_flags, context);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}

void parse_append(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context)
{
    *token_list = (*token_list)->next;
    if ((*token_list) == NULL)
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_outfile_redir_node(token_list, cmd, command_flags, context);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}

void parse_redir(t_token **token_list, t_cmd *cmd, t_context *context)
{
    ft_printf("parse_redir activated\n");

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
//ダメなところがあるまだシンタックスエラーをはじけてない、特に> WORD WORDとか