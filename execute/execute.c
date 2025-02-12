#include "../minishell.h"

int    pipe_process(char *cmd, char **envp);
void ft_execvp(char *cmd, char **envp);
void	here_doc(const char *limiter, int fd);

void handle_redirect(t_cmd *cmd) 
{
    t_infile_redir *ir = cmd->infile_redir;
	int flags;
	int	fd;
    while (ir) 
	{
		if (ir->redirection_flag == F_HEREDOC)
		{
			fd = open(ir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			here_doc(ir->filename, fd);
			close(fd);
			open(ir->filename, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink(ir->filename);
			ir = ir->next;
			continue;
		}
        fd = open(ir->filename, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
        ir = ir->next;
    }
    t_outfile_redir *or = cmd->outfile_redir;
    while (or) {
        flags = O_WRONLY | O_CREAT;
        if (or->redirection_flag == F_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(or->filename, flags, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        or = or->next;
    }
}

void execute_command(t_ast_node *node, char **envp, int input_fd, int output_fd) {
	char *tmp;
	char *cmds;
	t_command_args *current;

	current = node->command_node->command_args;
    pid_t pid = fork();
    if (pid == 0) {
        if (input_fd != STDIN_FILENO) 
			dup2(input_fd, STDIN_FILENO);
        if (output_fd != STDOUT_FILENO) 
			dup2(output_fd, STDOUT_FILENO);
        handle_redirect(node->command_node);
		cmds = "";
		cmds = ft_strjoin(cmds, current->string);
		current = current->next;
		while(current)
		{
			tmp = ft_strjoin(" ", current->string);
			cmds = ft_strjoin(cmds, tmp);
			current = current->next;
		}
		ft_execvp(cmds, envp);
    } else {
        waitpid(pid, NULL, 0);
    }
}

static void execute_pipeline(t_ast_node *node, char **envp, int input_fd) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) 
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == 0) 
	{
        close(fd[0]);
        dup2(input_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_command(node->pipe_node->left, envp, STDIN_FILENO, STDOUT_FILENO);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    if (pid == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        if (node->pipe_node->right->type == AST_PIPE) 
		{
            execute_pipeline(node->pipe_node->right, envp, STDIN_FILENO);
        } 
		else 
		{
            execute_command(node->pipe_node->right, envp, STDIN_FILENO, STDOUT_FILENO);
        }
        exit(EXIT_SUCCESS);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(-1, NULL, 0);
    waitpid(-1, NULL, 0);
}

void execute_ast(t_ast_node *node, char **envp) {
    if (!node) return;

    if (node->type == AST_PIPE) 
	{
        execute_pipeline(node, envp, STDIN_FILENO);
    }
	else
	{
        execute_command(node, envp, STDIN_FILENO, STDOUT_FILENO);
    }
}

int	main(int argc, char **argv, char **envp)
{

	char *line = "<< EOF cat";
    t_token *token = input_scanner(line);
    t_ast_node *tree = parse_tokens(&token);
    
   	while (1)
	{
		line = readline("minishell:");
		token = input_scanner(line);
		tree = parse_tokens(&token);
		execute_ast(tree, envp); 
	}
	return 0;
}

