/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:56 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 21:15:43 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_args(t_ast_node *node)
{
	t_command_args	*current;
	int				cnt;

	current = node->command_node->command_args;
	cnt = 0;
	while (current)
	{
		cnt++;
		current = current->next;
	}
	return (cnt);
}

char	**create_cmds(t_ast_node *node)
{
	t_command_args	*current;
	char			**cmds;
	int				i;

	current = node->command_node->command_args;
	cmds = malloc(sizeof(char *) * (count_args(node) + 1));
	i = 0;
	while (current)
	{
		cmds[i] = ft_strdup(current->string);
		i++;
		current = current->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

void	store_commands(t_ast_node *node, t_ast_node **cmds, int *count)
{
	while (node && node->type == AST_PIPE)
	{
		cmds[*count] = node->pipe_node->right;
		(*count)++;
		node = node->pipe_node->left;
	}
	if (node)
	{
		cmds[*count] = node;
		(*count)++;
	}
}

void	child_process(t_ast_node *cmd, int in_fd, int *pipe_fd,
		t_context *ctx)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (ctx->info->i < ctx->info->count - 1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	run_command(cmd, STDIN_FILENO, STDOUT_FILENO, ctx);
	exit(EXIT_FAILURE);
}

void	parent_process(int *in_fd, int *pipe_fd, int i, int count)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (i < count - 1)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}
