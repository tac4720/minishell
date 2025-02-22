/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:44:32 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/19 15:36:40 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_check(char *line, int *i)
{
	int	quote;

	if (line && line[*i] && (line[*i] == '\'' || line[*i] == '\"'))
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
	}
}

static void	print_quote_error(char *line, int *i, t_context *ctx)
{
	quote_check(line, i);
	if (line && line[*i] == '\0')
	{
		unclosed_quote(line, ctx);
	}
}

void	check_open_close(char *line, t_context *ctx)
{
	int		i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] == '\'')
			print_quote_error(line, &i, ctx);
		else if (line[i] == '\"')
			print_quote_error(line, &i, ctx);
		if (line[i])
			i++;
	}
}
