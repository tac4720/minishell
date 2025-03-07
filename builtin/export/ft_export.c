/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:44 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/07 14:48:40 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../builtin_execute/builtin.h"
#include "../../minishell.h"

static int	validate_var_name(char *arg)
{
	char	*eq_pos;
	size_t	name_len;
	size_t	i;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
		name_len = eq_pos - arg;
	else
		name_len = ft_strlen(arg);
	if (name_len == 0)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (i < name_len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_export_error(t_context *context)
{
	ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
	context->last_status = 1;
}

void	print_sorted_declare(t_map *environ)
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
		if (ft_strncmp(value, "@", 1) == 0)
			ft_printf("declare -x %s\n", list[i]);
		else
			ft_printf("declare -x %s=%s\n", list[i], value);
		free(list[i]);
		i++;
	}
	free(list);
}

void	ft_export(char **args, t_context *context)
{
	t_map	*env;
	int		j;
	int		status;

	env = context->environ;
	status = 0;
	if (!args[1])
	{
		print_sorted_declare(context->environ);
		free_and_exit(context, args, 0);
	}
	j = 1;
	while (args[j])
	{
		if (!validate_var_name(args[j]))
		{
			handle_export_error(context);
			status = 1;
		}
		else
			map_put(env, args[j]);
		j++;
	}
	free_and_exit (context, args, status);
}

void	ft_export_p(char **args, t_context *context)
{
	t_map	*env;
	int		j;
	int		status;

	env = context->environ;
	status = 0;
	if (!args[1])
	{
		print_sorted_declare(context->environ);
		context->last_status = 0;
	}
	j = 1;
	while (args[j])
	{
		if (!validate_var_name(args[j]))
		{
			handle_export_error(context);
			status = 1;
		}
		else
			map_put(env, args[j]);
		j++;
	}
	context->last_status = status;
}
