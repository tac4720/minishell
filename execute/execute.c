#include "../minishell.h"
// void	fatal_error(const char *msg)
// {
// 	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
// 	exit(1);
// }

int execute(t_ast_node *node, t_context *context)
{
	extern char	**environ;

	t_cmd *cmd = (t_cmd *)node->node;
	char		*argv[] = {cmd->name->input, NULL};
    char        *tmp;
	pid_t		pid;
	int			wstatus;


	printf("%s\n", cmd->name->input);
	// pid = fork();
	// if (pid < 0)
	// 	fatal_error("fork");
	// else if (pid == 0)
	// {

	// 	if (builtin_execute(node->node->name->input, context))
	// 	{
	// 		return (0);
	// 	}
    //     if(strchr(node->node->t_input->input, '/') == NULL)
    //     {
    //         tmp = node->node->t_input->input;
    //         node->node->t_input->input = make_path(node->node->t_input->input);
    //         free(tmp);
    //         execve(node->node->t_input->input, argv, environ);
    //     }
	// 	// child process
	// 	execve(node->node->t_input->input, argv, environ);
	// 	fatal_error("execve");
	// }
	// else
	// {
	// 	// parent process
	// 	wait(&wstatus);
	// 	return (WEXITSTATUS(wstatus));
	// }

    return (0);

}
// int read_tree_exec(t_context *context, t_ast_node *node)
// {
// 	if (node->type == AST_COMMAND)
// 		execute(node, context);

// 	// 	expand(node);
// 	// if (node->type == AST_PIPE)
// 	// 	execute_pipeline(node);
// 	return (0);
// }