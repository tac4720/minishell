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

void	ft_unset(char **args, t_context *context)
{
	t_map	*env;
	int		status;
	int		i;

	env = context->environ;
	status = 0;
	i = 1;
	while (args[i])
	{
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
	i = 1;
	while (args[i])
	{
		map_unset(env, args[i]);
		i++;
	}
	context->last_status = status;
}
