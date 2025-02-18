#include "exec.h"

int		count_args(t_ast_node *node)
{
	t_command_args	*current;
	char			**cmds;
	int				cnt;

	current =node->command_node->command_args;
	cnt = 0;
	while (current) 
	{
		cnt++;	
		current = current->next;
	}
	return(cnt);
}

char	**create_cmds(t_ast_node *node)
{
	t_command_args	*current;
	char			**cmds;
	int				i;

	current = node->command_node->command_args;
	cmds = malloc(sizeof(char *) * (count_args(node) + 1));
	//if (!cmds)
		//終了処理
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


