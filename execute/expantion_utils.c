/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:10 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/07 14:54:07 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*expand_status(const char *str, int *i, char *result, t_context *ctx)
{
	char	*expand_str;

	if (str[*i + 1] == '?')
	{
		expand_str = ft_itoa(ctx->last_status);
		result = join_and_free(result, expand_str, 1);
		*i += 2;
	}
	return (result);
}

char	*get_env_value(const char *str, int *i)
{
	char	*var_name;
	int		start;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

char	*expand_env_var(const char *str, int *i, char *result, t_context *ctx)
{
	char	*var_name;
	char	*expand_str;

	(*i)++;
	var_name = get_env_value(str, i);
	expand_str = map_get(ctx->environ, var_name);
	free(var_name);
	if (expand_str)
	{
		result = join_and_free(result, expand_str, 0);
	}
	else
	{
		result = join_and_free(result, "", 0);
	}
	return (result);
}

char	*expand_normal_str(const char *str, int *i, char *result)
{
	char	*tmp;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	result = join_and_free(result, tmp, 1);
	return (result);
}

char	*expand_helper(const char *str, t_context *ctx)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\0' || str[i + 1] == ' ')
			{
				result = join_and_free(result, "$", 0);
				i++;
				continue ;
			}
			if (str[i + 1] == '?')
				result = expand_status(str, &i, result, ctx);
			else
				result = expand_env_var(str, &i, result, ctx);
			continue ;
		}
		result = expand_normal_str(str, &i, result);
	}
	return (result);
}
