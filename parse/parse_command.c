#include "minishell.h"

void parse_args(t_token **token_list, t_cmd *cmd)
{
    printf("parse_args activated\n");
    t_command_args *tmp;

    if (cmd->command_args == NULL)
    {
        printf("testa\n");

        cmd->command_args = ft_calloc(1, sizeof(t_command_args));
        cmd->command_args->string = ft_strdup((*token_list)->str);
        cmd->command_args->next = NULL;
        cmd->command_args->flag = (*token_list)->flag;
        printf("testb\n");

    }
    else
    {
        tmp = cmd->command_args;

        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = ft_calloc(1, sizeof(t_command_args));
        tmp->next->string = ft_strdup((*token_list)->str);
        tmp->next->next = NULL;
        tmp->next->flag = (*token_list)->flag;
    }
    *token_list = (*token_list)->next;
}

void add_cmd_node(t_token **token_list, t_cmd *cmd)
{
    printf("add_cmd_node activated\n");
    
        while ((*token_list) != NULL)//ここでまいかいせぐふぉしちゃう
        {
            if ((*token_list)->type != PIPE_OP)
            {
                if ((*token_list)->type == HEREDOC || 
                (*token_list)->type == APPEND || 
                (*token_list)->type == FILE_IN || 
                (*token_list)->type == FILE_OUT)
                {
                    parse_redir(token_list, cmd);
                }
                else
                {
                    parse_args(token_list, cmd);
                    printf("testc\n");

                }
            }
        }

}

t_ast_node *new_cmd_node(t_cmd *cmd, t_token **token_list)
{
    t_ast_node  *new_node;
    printf("new_cmd_node activated\n");

    new_node = ft_calloc(1, sizeof(t_ast_node));
    new_node->command_node = cmd;
    if (cmd->num_of_words == 1) //ここもう使ってないよな
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
    printf("token_content when parse_cmd activated:%s\n", (*token_list)->str);

    t_cmd *cmd;
    cmd = ft_calloc(1, sizeof(t_cmd));
    //mallocエラー処理
    //今のところいらない//cmd->num_of_words = word_count(*token_list);//あとでかく,arg_countとかのほうが名前よさそう？
    cmd->in_fd = -2;
	cmd->out_fd = -2;
	cmd->command_args = NULL;
    cmd->infile_redir = NULL;
    cmd->outfile_redir = NULL;
    return (new_cmd_node(cmd, token_list));//ここからかく
}
