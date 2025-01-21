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

t_ast_node *new_cmd_node(t_cmd *cmd, t_token **token_list)
{
    t_ast_node  *node;

    node = ft_calloc(1, sizeof(t_ast_node));
    if (cmd->n == 1)
    {
        *token_list = (*token_list)->next;
    }
    else
    {
        *token_list = (*token_list)->next;
        while(*token_list && ((*token_list)->type == WORD || (*token_list)->type == ENV_PARAM))
        {
            add_cmd_node(token_list, &cmd);
        }
    }
    node->node = (void *)cmd;
    node->type = AST_COMMAND;
    node->in_fd = -2;
    node->out_fd = -2;
    return (node);
}

int word_count(t_token *token_list)
{
    int n;

    n = 0;
    while (token_list && (token_list->type == WORD || token_list->type == ENV_PARAM))
	{
		n++;
		token_list = token_list->next;
	}
    return n;
}

t_ast_node *parse_cmd(t_token **token_list)
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
    return (new_cmd_node(cmd, token_list));//ここからかく
}
