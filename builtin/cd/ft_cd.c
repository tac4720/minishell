/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:30 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/19 17:20:44 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../builtin_execute/builtin.h"

static void	update_pwd(t_context *context)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		context->last_status = 1;
	}
	map_set(context->environ, "PWD", cwd);
	context->last_status = 0;
}

void	error_check(char **args, t_context *context)
{
	if (args[2] != NULL)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		context->last_status = 1;
	}
}

void	ft_cd(char **args, t_context *context)
{
	char	*target_dir;
	int		ret;

	error_check(args, context);
	target_dir = args[1];
	if (target_dir == NULL)
	{
		target_dir = map_get(context->environ, "HOME");
		if (target_dir == NULL)
		{
			context->last_status = 1;
		}
	}
	ret = chdir(target_dir);
	if (ret != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		context->last_status = 1;
		exit (1);
	}
	update_pwd(context);
	free_and_exit(context, args, context->last_status);
}

void	ft_cd_p(char **args, t_context *context)
{
	char	*target_dir;
	int		ret;

	error_check(args, context);
	target_dir = args[1];
	if (target_dir == NULL)
	{
		target_dir = map_get(context->environ, "HOME");
		if (target_dir == NULL)
		{
			context->last_status = 1;
		}
	}
	ret = chdir(target_dir);
	if (ret != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		context->last_status = 1;
	}
	if (context->last_status != 1)
		update_pwd(context);
}
