/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:44:27 by tac               #+#    #+#             */
/*   Updated: 2025/03/01 21:59:46 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	info_set(t_ast_node *node, t_ast_node **cmds, t_exec_info *info,
	t_context *ctx)
{
	info->count = 0;
	info->envp = ctx->env;
	store_commands(node, cmds, &info->count);
	reverse_commands(cmds, info->count);
	info->i = 0;
}

void	wait_for_child(t_context *ctx, pid_t pid)
{
	waitpid(pid, &(ctx->last_status), 0);
	if (WIFEXITED(ctx->last_status))
	{
		ctx->last_status = WEXITSTATUS(ctx->last_status);
	}
	else if (WIFSIGNALED(ctx->last_status))
	{
		ctx->last_status = WTERMSIG(ctx->last_status) + 128;
	}
}

void	wait_for_children(t_context *ctx)
{
	while (waitpid(-1, &(ctx->last_status), 0) > 0)
	{
		ctx->last_status = WEXITSTATUS(ctx->last_status);
	}
}

void	handle_sigint_in_process(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	setup(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint_in_process;
	sigaction(SIGINT, &sa, NULL);
}
