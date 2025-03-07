/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:36 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/07 14:59:05 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_execute/builtin.h"
#include <stdlib.h>

void	print_sorted(t_map *environ)
{
	char	**list;
	char	*value;
	int		i;

	i = 0;
	list = hashmap_to_list(environ);
	if (!list)
		return ;
	sort_list(list);
	while (list[i])
	{
		value = map_get(environ, list[i]);
		if (ft_strncmp(value, "@", 1) != 0)
			ft_printf("%s=%s\n", list[i], value);
		free(list[i]);
		i++;
	}
	free(list);
}

void	ft_env(char **args, t_context *context)
{
	t_map	*env;

	env = context->environ;
	if (args[1] != NULL)
	{
		free_and_exit(context, args, 1);
	}
	print_sorted(env);
	free_and_exit(context, args, 0);
}

void	ft_env_p(char **args, t_context *context)
{
	t_map	*env;

	env = context->environ;
	if (args[1] != NULL)
	{
		free_and_exit(context, args, 1);
	}
	print_sorted(env);
	context->last_status = 0;
}
