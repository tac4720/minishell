#include "minishell.h"

void add_redir_node(t_token **token_list, t_cmd *cmd, int command_flag)//outfile,infile,appendすべてに対応していない。
{
    t_redir *tmp;

    if (cmd->redirection == NULL)
    {
        cmd->redirection = ft_calloc(1, sizeof(t_redir));
        cmd->redirection->filename = ft_strdup((*token_list)->str);
        cmd->redirection->next = NULL;
        cmd->redirection->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    else
    {
        tmp = cmd->redirection;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = ft_calloc(1, sizeof(t_redir));
        tmp->next->filename = ft_strdup((*token_list)->str);
        tmp->next->next = NULL;
        cmd->redirection->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    return ;
}

void parse_heredoc(t_token **token_list, t_cmd *cmd)
{

}

void parse_append(t_token **token_list, t_cmd *cmd, int command_flags)
{
    cmd->redirection = ft_calloc(1, sizeof(t_redir));
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        exit(0);
    }
}

void parse_file_in(t_token **token_list, t_cmd *cmd, int command_flags)
{
    cmd->redirection = ft_calloc(1, sizeof(t_redir));
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        exit(0);
    }
}

void parse_file_out(t_token **token_list, t_cmd *cmd, int command_flags)
{
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        exit(0);
    }
}
void parse_redir(t_token **token_list, t_cmd *cmd)
{
    while ((*token_list) != NULL && ((*token_list)->type != PIPE_OP || WORD || ERROR))
    {
        if ((*token_list)->type == HEREDOC)
        {
            // parse_heredoc(token_list, cmd, F_HEREDOC);
        }
        if ((*token_list)->type == APPEND)
        {
            parse_append(token_list, cmd, F_APPEND);
        }
        if ((*token_list)->type == FILE_IN)
        {
            parse_file_in(token_list, cmd, F_INFILE);

        }
        if ((*token_list)->type == FILE_OUT)
        {
            parse_file_out(token_list, cmd, F_OUTFILE);
        }
    }    
}
//ダメなところがあるまだシンタックスエラーをはじけてない、特に> WORD WORDとか