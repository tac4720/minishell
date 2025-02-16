/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:24:15 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/16 16:07:07 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open_close(char *line)
{
    int i;
    int quote;

    i = 0;
    while (line && line[i])
	{
        if (line[i] == '\'' || line[i] == '\"')
        {
            quote = line[i];
            (i)++;
            while (line[i] && line[i] != quote)
            {
                (i)++;
                if (line[i] == '\0')
                {
                    printf("unclosed quote\n");
                    exit(-1);//unclosed quoteによるエラー

                }
            }
        }
        else
        {
            i++;
        }
	}
}

void malloc_error(t_context *context)
{
    //token列のfree
    if (context->token_list_top)
        free_tokens(context->token_list_top);

    //readlineでもらったlineのfree
    if (context->readline != NULL)
        free(context->readline);

    //最後にcontextのfreeその中で必要なもの
    free(context);


    printf("malloc error\n");
    exit(1);//exitで何番返す？,marieのminishell参照
}
//parseのエラー処理
void error_in_parse(t_context *context)
{
    printf("error in parse\n");
    if (context == NULL)
        exit(1);//exitで何番返す？,marieのminishell参照
    //token列のfree
    if (context->token_list_top != NULL)
        free_tokens(context->token_list_top);

    //readlineでもらったlineのfree
    if (context->readline != NULL)
        free(context->readline);

    //astのfree
    free_ast_tree(context->root_node);

    //environのfree
    if (context->environ != NULL)
        free_map(context->environ);
    //最後にcontextのfree
    free(context);
    exit(1);//exitで何番返す？,marieのminishell参照
}
void free_tokens(t_token *token)
{
    t_token *tmp;

    while (token != NULL)
    {
        tmp = token;
        token = token->next;
        free(tmp->str);
        free(tmp);
    }
}