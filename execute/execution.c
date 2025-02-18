/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:01 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:33 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	run_command(t_ast_node *node, int input_fd, int output_fd,
	t_context *ctx)
{
	char	**tmp;
	char	**cmds;

	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	handle_redirect(node->command_node);
	tmp = create_cmds(node);
	cmds = remove_empty_commands(tmp);
	free_commands(tmp);
	if (!cmds || !cmds[0])
	{
		free_commands(cmds);
		exit(0);
	}
	ft_execvp(cmds, ctx->env, ctx);
	free(cmds);
	exit(0);
}

void	execute_command(t_ast_node *node, int input_fd, int output_fd,
	t_context *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		run_command(node, input_fd, output_fd, ctx);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &(ctx->last_status), 0);
		ctx->last_status = WEXITSTATUS(ctx->last_status);
	}
}

void	execute_pipeline(t_ast_node *node, char **envp, int input_fd,
	t_context *ctx)
{
	t_ast_node	*cmds[1024];
	t_exec_info	info;
	int			pipe_fd[2];
	int			in_fd;
	pid_t		pid;

	info_set(node, cmds, &info, ctx);
	ctx->info = &info;
	in_fd = input_fd;
	while (info.i < info.count)
	{
		if (info.i < info.count - 1 && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
			child_process(cmds[info.i], in_fd, pipe_fd, ctx);
		parent_process(&in_fd, pipe_fd, info.i, info.count);
		info.i++;
	}
	while (waitpid(-1, &(ctx->last_status), 0) > 0)
		ctx->last_status = WEXITSTATUS(ctx->last_status);
}

void	execute_ast(t_ast_node *node, char **envp, t_context *ctx)
{
	if (!node)
		return ;
	if (node->type == AST_PIPE)
	{
		execute_pipeline(node, envp, STDIN_FILENO, ctx);
	}
	else
	{
		execute_command(node, STDIN_FILENO, STDOUT_FILENO, ctx);
	}
}
