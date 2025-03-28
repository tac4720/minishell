/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:25:57 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 16:25:57 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes_flag(int *i, int *flag, char *str)
{
	if (str[*i] == '\'' )
	{
		*flag |= F_SQUOTES;
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	else if (str[*i] == '\"')
	{
		*flag |= F_DQUOTES;
		(*i)++;
		while (str[*i] && str[*i] != '\"')
		{
			if (str[*i] && str[*i] == '$')
				*flag |= F_DOLLAR_IN_DQUOTES;
			(*i)++;
		}
	}
	else
	{
		(*i)++;
	}
}

int	check_flags(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i])
		check_quotes_flag(&i, &flag, str);
	if (ft_strchr(str, '='))
		flag |= F_ASSIGNMENT;
	return (flag);
}

void	analyze_word(char **s, t_token *token, t_context *context)
{
	int	n;

	n = 0;
	while (*(*s + n) && !ft_strchr(OPERATORS, *(*s + n))
		&& !is_blank(*(*s + n)))
	{
		quote_check(*s, &n);
		if (*(*s + n))
			n++;
	}
	token->str = ft_substr(*s, 0, n);
	if (token->str == NULL)
	{
		free(token);
		malloc_error(context);
	}
	token->flag = check_flags(token->str);
	*s += n;
}

t_token	*get_word_token(char **s, t_context *context)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		malloc_error(context);
	analyze_word(s, new_token, context);
	if (new_token->flag & F_DOLLAR || new_token->flag & F_DOLLAR_IN_DQUOTES)
		new_token->type = ENV_PARAM;
	else
		new_token->type = WORD;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}
