#include "exec.h"

void execute_command(t_ast_node *node, char **envp, int input_fd, int output_fd, t_context *ctx)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		 run_command(node, envp, input_fd, output_fd, ctx);
		 exit(EXIT_FAILURE);
	} 
	else
	{
		 waitpid(pid, &(ctx->last_status), 0);
		 ctx->last_status = WEXITSTATUS(ctx->last_status);
	}
}

 void	reverse_commands(t_ast_node **cmds, int count)
{
	int			i;
	t_ast_node	*temp;

	i = 0;
	while (i < count / 2)
	{
		temp = cmds[i];
		cmds[i] = cmds[count - 1 - i];
		cmds[count - 1 - i] = temp;
		i++;
	}
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
		t_exec_info *info, t_context *ctx)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (info->i < info->count - 1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	run_command(cmd, info->envp, STDIN_FILENO, STDOUT_FILENO, ctx);
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
