#include "minishell.h"

void add_cmd_node(t_token **token_list, t_cmd **cmd)
{
    t_input *tmp;

    tmp = (*cmd)->args;
    if (!(*cmd)->args)
    {
        (*cmd)->args = ft_calloc(1, sizeof(t_input));
        //mallocエラー処理
        (*cmd)->args->flag = (*token_list)->cmd->flag;
		(*cmd)->args->input = ft_strdup((*token_list)->cmd->input);
		(*cmd)->args->next = NULL;
		(*cmd)->args->prev = NULL;
    }
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = ft_calloc(1, sizeof(t_input));
        //mallocエラー処理
        tmp->next->flag = (*token_list)->cmd->flag;
		tmp->next->input = ft_strdup((*token_list)->cmd->input);
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
        
    }
    *token_list = (*token_list)->next;
}
t_ast_node *new_cmd_node(t_cmd *cmd, t_token **token_list, t_redir **red)
{
    t_ast_node  *node;

    node = ft_calloc(1, sizeof(t_ast_node));
    if (cmd->n == 1)
        *token_list = (*token_list)->next;
    while (*token_list && ((*token_list)->type == WORD || (*token_list) == ENV_PARAM \
    || (*token_list)->type == FILE_OUT || (*token_list)->type == FILE_IN \
	|| (*token_list)->type == APPEND || (*token_list)->type == HEREDOC))
    {
        if ((*token_list)->type == FILE_OUT || (*token_list)->type == FILE_IN \
		|| (*token_list)->type == APPEND || (*token_list)->type == HEREDOC)
			*red = parse_redir(token_list, red);
        else
            add_cmd_node(token_list, &cmd);
    }
    node->node = (void *)cmd;
    node->red_lst = NULL;
    node->type = AST_COMMAND;
    node->in_fd = -2;
    node->out_fd = -2;
    return (node);
}
t_ast_node *parse_cmd(t_token **token_list, t_redir **redirection_list)
{
    t_cmd *cmd;

    cmd = ft_calloc(1, sizeof(t_cmd));
    //mallocエラー処理
    cmd->n = word_count(*token_list);//あとでかく,arg_countとかのほうが名前よさそう？
    cmd->in_fd = -2;
	cmd->out_fd = -2;
	cmd->name = ft_calloc(1, sizeof(t_input));
	    //mallocエラー処理
	cmd->name->flag = (*token_list)->cmd->flag;
	cmd->name->input = ft_strdup((*token_list)->cmd->input);
    if (cmd->n < 2)
        cmd->args = NULL;
    else
        (*token_list) = (*token_list)->next;//ここ疑問、parse_redirectionとの矛盾が生じないか？
    return (new_cmd_node(cmd, token_list, redirection_list));//ここからかく
}
t_ast_node *parse_cmd_line(t_token **token_list)//parse_cmd_argとかの名前に変えるのはどうでしょうか
{
    t_ast_node *command;
    t_redir    *redirection_list;


    command = NULL;
    redirection_list = NULL;
    if ((*token_list) != PIPE_OP)
    {
        redirection_list = parse_redir(token_list, &redirection_list);
        if ((*token_list)->type != PIPE_OP)
            command = parse_cmd(token_list, &redirection_list);
    }
    command = parse_cmd_helper(command, redirection_list);
    return (command);
}

t_ast_node *parse_cmd_helper(t_ast_node cmd, t_redir *red_lst)
{
    t_cmd   *tmp;


    if (cmd)
    {

    } 
}