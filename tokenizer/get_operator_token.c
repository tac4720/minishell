/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:54:04 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 16:54:04 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(char **s)
{
	(*s)++;
	if (**s != '|')
	{
		return (PIPE_OP);
	}
	return (ERROR);
}

int	check_redir(char **s)
{
	if (**s == '<')
	{
		(*s)++;
		if (**s == '<')
		{
			(*s)++;
			return (HEREDOC);
		}
		return (FILE_IN);
	}
	else if (**s == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			(*s)++;
			return (APPEND);
		}
		return (FILE_OUT);
	}
	return (ERROR);
}

void	operator_input(t_token *token, t_context *context)
{
	if (token->type == HEREDOC)
		token->str = ft_strdup("<<");
	else if (token->type == APPEND)
		token->str = ft_strdup(">>");
	else if (token->type == FILE_IN)
		token->str = ft_strdup("<");
	else if (token->type == FILE_OUT)
		token->str = ft_strdup(">");
	else if (token->type == PIPE_OP)
		token->str = ft_strdup("|");
	else if (token->type == ERROR)
		token->str = ft_strdup("&");
	if (token->str == NULL)
	{
		free(token);
		free_tokens(context->token_list_top);
		if (context->readline != NULL)
			free(context->readline);
		if (context->environ != NULL)
			free_map(context->environ);
		free(context);
		exit(1);
	}
}

int	get_op_type(char **s)
{
	if (**s == '|')
		return (check_pipe(s));
	else if (**s == '<')
		return (check_redir(s));
	else if (**s == '>')
		return (check_redir(s));
	return (ERROR);
}

t_token	*get_operator_token(char **s, t_context *context)
{
	t_token	*new_token;

	if (!s || !(*s))
		return (NULL);
	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		malloc_error(context);
	new_token->type = get_op_type(s);
	operator_input(new_token, context);
	new_token->flag = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}
