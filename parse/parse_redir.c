#include "../minishell.h"

void add_infile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag)//outfile,infile,appendすべてに対応していない。
{
    t_infile_redir *tmp;

    if (cmd->infile_redir == NULL)
    {
        cmd->infile_redir = ft_calloc(1, sizeof(t_infile_redir));
        cmd->infile_redir->filename = ft_strdup((*token_list)->str);
		printf(cmd->infile_redir->filename);
		// remove_quotes(cmd->infile_redir->filename);
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
        tmp->next->filename = ft_strdup((*token_list)->str);
		printf(tmp->next->filename);
		// remove_quotes(cmd->infile_redir->filename);
        tmp->next->next = NULL;
        cmd->infile_redir->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    return ;
}

void add_outfile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag)//outfile,infile,appendすべてに対応していない。
{
    t_outfile_redir *tmp;

    if (cmd->outfile_redir == NULL)
    {
        cmd->outfile_redir = ft_calloc(1, sizeof(t_outfile_redir));
        cmd->outfile_redir->filename = ft_strdup((*token_list)->str);
		// remove_quotes(cmd->infile_redir->filename);
        ft_printf("test:%s\n", cmd->outfile_redir->filename);
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
        tmp->next->filename = ft_strdup((*token_list)->str);
		remove_quotes(cmd->infile_redir->filename);
        tmp->next->next = NULL;
        cmd->outfile_redir->redirection_flag |= command_flag;
        *token_list = (*token_list)->next;
    }
    return ;
}

void parse_heredoc(t_token **token_list, t_cmd *cmd, int command_flags)
{
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_infile_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}



void parse_file_in(t_token **token_list, t_cmd *cmd, int command_flags)
{
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_infile_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}

void parse_file_out(t_token **token_list, t_cmd *cmd, int command_flags)
{
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_outfile_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}

void parse_append(t_token **token_list, t_cmd *cmd, int command_flags)
{
    *token_list = (*token_list)->next;
    if ((*token_list)->type == WORD || ENV_PARAM)//redirectionの引数に環境変数いれられる？
    {
        add_outfile_redir_node(token_list, cmd, command_flags);
    }
    else
    {
        ft_printf("syntax error redirection\n");
        exit(0);
    }
}

void parse_redir(t_token **token_list, t_cmd *cmd)
{
    // ft_printf("parse_redir activated\n");

    if ((*token_list)->type == HEREDOC)
    {
        parse_heredoc(token_list, cmd, F_HEREDOC);
        return ;
    }
    if ((*token_list)->type == APPEND)
    {
        parse_append(token_list, cmd, F_APPEND);
        return ;
    }
    if ((*token_list)->type == FILE_IN)
    {
        parse_file_in(token_list, cmd, F_INFILE);
        return ;
    }
    if ((*token_list)->type == FILE_OUT)
    {
        parse_file_out(token_list, cmd, F_OUTFILE);
        return ;
    }
}
//ダメなところがあるまだシンタックスエラーをはじけてない、特に> WORD WORDとか
