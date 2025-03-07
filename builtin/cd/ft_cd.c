/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:30 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/07 15:07:20 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_execute/builtin.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	update_pwd(t_context *context)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		pwd = map_get(context->environ, "PWD");
		if (pwd)
		{
			pwd = ft_strdup(pwd);
			if (pwd)
			{
				map_set(context->environ, "OLDPWD", pwd);
				free(pwd);
			}
		}
		context->last_status = 1;
		return ;
	}
	map_set(context->environ, "OLDPWD", map_get(context->environ, "PWD"));
	map_set(context->environ, "PWD", cwd);
	context->last_status = 0;
}

void	print_error(char *target_dir)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(target_dir, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	error_check(char **args, t_context *ctx)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		ctx->last_status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(char **args, t_context *context)
{
	char	*target_dir;
	int		ret;

	if (error_check(args, context))
		free_and_exit(context, args, 1);
	target_dir = args[1];
	if (target_dir == NULL)
	{
		target_dir = map_get(context->environ, "HOME");
		if (target_dir == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			context->last_status = 1;
			free_and_exit(context, args, 1);
		}
	}
	ret = chdir(target_dir);
	if (ret != 0)
	{
		print_error(target_dir);
		context->last_status = 1;
		free_and_exit(context, args, 1);
	}
	update_pwd(context);
	free_and_exit(context, args, context->last_status);
}

void	ft_cd_p(char **args, t_context *context)
{
	char	*target_dir;
	int		ret;

	if (error_check(args, context))
		return ;
	target_dir = args[1];
	if (target_dir == NULL)
	{
		target_dir = map_get(context->environ, "HOME");
		if (target_dir == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			context->last_status = 1;
			return ;
		}
	}
	ret = chdir(target_dir);
	if (ret != 0)
	{
		print_error(target_dir);
		context->last_status = 1;
		return ;
	}
	update_pwd(context);
}
