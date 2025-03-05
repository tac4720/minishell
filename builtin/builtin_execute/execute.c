/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:26 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/19 17:03:01 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include <stdio.h>

int	is_builtin(char *str)
{
	int			i;
	char		*builtin_cmds[8];
	size_t		cmd_len;

	i = 0;
	builtin_cmds[0] = "cd";
	builtin_cmds[1] = "echo";
	builtin_cmds[2] = "env";
	builtin_cmds[3] = "exit";
	builtin_cmds[4] = "export";
	builtin_cmds[5] = "pwd";
	builtin_cmds[6] = "unset";
	builtin_cmds[7] = NULL;
	while (builtin_cmds[i])
	{
		cmd_len = ft_strlen(builtin_cmds[i]);
		if (ft_strncmp(str, builtin_cmds[i], cmd_len + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	free_and_exit(t_context *ctx, char **args, int status)
{
	(void)(ctx);
	free_commands(args);
	exit(status);
}

void	free_and_exit_p(t_context *ctx, char **args, int status)
{
	int	last_status;

	last_status = ctx->last_status;
	free(ctx->input);
	free_ast_tree(ctx->root_node);
	clean(ctx);
	free_commands(args);
	ft_putstr_fd("exit\n", 2);
	if (status == -1)
		exit(last_status);
	exit(status);
}

int	builin_execute_p(char **args, t_context *context)
{
	int	select;

	select = is_builtin(args[0]);
	if (select == 0)
		ft_cd_p(args, context);
	else if (select == 2)
		ft_env_p(args, context);
	else if (select == 3)
		ft_exit_p(args, context);
	else if (select == 4)
		ft_export_p(args, context);
	else if (select == 6)
		ft_unset_p(args, context);
	return (0);
}

int	builtin_execute(char **args, t_context *context)
{
	int	select;

	select = is_builtin(args[0]);
	if (select == 0)
		ft_cd(args, context);
	else if (select == 1)
		ft_echo(args, context);
	else if (select == 2)
		ft_env(args, context);
	else if (select == 3)
		ft_exit(args, context);
	else if (select == 4)
		ft_export(args, context);
	else if (select == 5)
		ft_pwd(args, context);
	else if (select == 6)
		ft_unset(args, context);
	return (0);
}
