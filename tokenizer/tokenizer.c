/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:54:31 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 16:54:31 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token *get_token(char **s, t_context *context)
{
	if (!(*s))
		return (NULL);
	while (**s && is_blank(**s))
	{
		(*s)++;
	}
	if (**s && ft_strchr(OPERATORS, **s))
		return (get_operator_token(s, context));
	else if (**s)
		return (get_word_token(s, context));
	
	return (NULL);
}

t_token *last_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void token_add(t_token **token_list, t_token *token, t_context *context)
{
	t_token *tmp;
	t_token *last;
	if (token == NULL)
		return ;
	if (*token_list == NULL)
	{
		context->token_list_top = token;
		*token_list = token;
		return;
	}
	else
	{
		last = last_token(*token_list);
		last->next = token;
		token->prev = last;
	}
	return;
}

t_token *input_scanner(char *line, t_context *context)
{
	t_token *token_list;
	t_token *token;

	token_list = NULL;
	token = NULL;
	context->readline = line;
	while(*line)
	{
		token = get_token(&line, context);
		token_add(&token_list, token, context);
	}
	return (token_list);
}
