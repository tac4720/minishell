#include "minishell.h"


void add_cmd_node(t_token **token_list, t_cmd *cmd)
{
    int i;
    t_command_args *tmp;

    i = 0;
    while (i < cmd->num_of_words)
    {
        if ((*token_list)->type == HEREDOC || APPEND || FILE_IN || FILE_OUT)
        {
            parse_redir(token_list, cmd);
        }
        if (cmd->command_args == NULL)
        {
            cmd->command_args = ft_calloc(1, sizeof(t_command_args));
            cmd->command_args->string = ft_strdup((*token_list)->str);
            cmd->command_args->next = NULL;
            cmd->command_args->flag = (*token_list)->flag;
            tmp = cmd->command_args;
            tmp->next = ft_calloc(1, sizeof(t_command_args));
            tmp = tmp->next;            
        }
        else
        {
            tmp->string = ft_strdup((*token_list)->str);
            tmp->next = NULL;
            tmp->flag = (*token_list)->flag;
            if (i < cmd->num_of_words - 1)
                tmp->next = ft_calloc(1, sizeof(t_command_args));
            tmp = tmp->next;
        }
        i++;
        *token_list = (*token_list)->next;
    }
}

t_ast_node *new_cmd_node(t_cmd *cmd, t_token **token_list)
{
    t_ast_node  *new_node;

    new_node = ft_calloc(1, sizeof(t_ast_node));
    new_node->command_node = cmd;
    if (cmd->num_of_words == 1)
    {//もしWORDかENV_PARAM以外だったらはじく
        cmd->command_args = ft_calloc(1, sizeof(t_command_args));
        new_node->command_node->command_args->string = ft_strdup((*token_list)->str);
        new_node->command_node->command_args->next = NULL;
        new_node->command_node->command_args->flag = (*token_list)->flag;
        *token_list = (*token_list)->next;
    }
    else
    {
        add_cmd_node(token_list, cmd);
    }
    new_node->type = AST_COMMAND;
    return (new_node);
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
    printf("num_of_words:%d\n", n);

    return n;
}

t_ast_node *parse_cmd(t_token **token_list)
{
    printf("parse_cmd activated\n");

    t_cmd *cmd;
    cmd = ft_calloc(1, sizeof(t_cmd));
    //mallocエラー処理
    cmd->num_of_words = word_count(*token_list);//あとでかく,arg_countとかのほうが名前よさそう？
    cmd->in_fd = -2;
	cmd->out_fd = -2;
    cmd->command_flag = 0;//ここは0でいいのか？マクロとの兼ね合いに注意
    cmd->redirection = NULL;
    return (new_cmd_node(cmd, token_list));//ここからかく
}
