/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:51 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/19 17:16:48 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_execute/builtin.h"
#include <stdio.h>
#include <stdbool.h>

static bool	is_valid_identifier(const char *str)
{
	if (str[0] == '\0' || (!(str[0] >= 'A' && str[0] <= 'Z')
			&& !(str[0] >= 'a' && str[0] <= 'z') && str[0] != '_'))
		return (false);
	while (*str)
	{
		if (!((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')
				|| (*str >= '0' && *str <= '9') || *str == '_'))
			return (false);
		str++;
	}
	return (true);
}

void	ft_unset(char **args, t_context *context)
{
	t_map	*env;
	int		status;
	int		i;

	env = context->environ;
	status = 0;
	if (args[1] == NULL)
		free_and_exit (context, args, 0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			status = 1;
		}
		else
			map_unset(env, args[i]);
		i++;
	}
	free_and_exit (context, args, status);
}

void	ft_unset_p(char **args, t_context *context)
{
	t_map	*env;
	int		status;
	int		i;

	env = context->environ;
	status = 0;
	if (args[1] == NULL)
		context->last_status = 1;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			status = 1;
		}
		else
			map_unset(env, args[i]);
		i++;
	}
	context->last_status = 0;
}
