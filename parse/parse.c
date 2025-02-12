#include "../minishell.h"

t_ast_node  *parse_tokens(t_token **token_list)
{
    t_ast_node *tree;

    tree = NULL;
    if(!token_list)
        return (NULL);
    tree = parse_pipeline(token_list);
    // printf("パースが完了しました\n");
    return (tree);
}

static void print_indent(int depth) {
    for (int i = 0; i < depth * 4; i++)
        printf(" ");
}

static void print_redirections(t_cmd *cmd, int depth) {
    t_infile_redir *ir = cmd->infile_redir;
    t_outfile_redir *or = cmd->outfile_redir;

    while (ir) {
        print_indent(depth);
        printf("├─IN ");
        switch(ir->redirection_flag) {
            case F_INFILE:  printf("< %s\n", ir->filename); break;
            case F_HEREDOC: printf("<< %s\n", ir->filename); break;
        }
        ir = ir->next;
    }

    while (or) {
        print_indent(depth);
        printf("├─OUT ");
        switch(or->redirection_flag) {
            case F_OUTFILE: printf("> %s\n", or->filename); break;
            case F_APPEND:  printf(">> %s\n", or->filename); break;
        }
        or = or->next;
    }
}

void print_ast(t_ast_node *node, int depth) {
    if (!node) return;

    print_indent(depth);
    
    switch(node->type) {
        case AST_PIPE:
            printf("PIPE\n");
            print_indent(depth);
            printf("├─LEFT\n");
            print_ast(node->pipe_node->left, depth + 1);
            print_indent(depth);
            printf("└─RIGHT\n");
            print_ast(node->pipe_node->right, depth + 1);
            break;
            
        case AST_COMMAND:
            printf("COMMAND\n");
            print_redirections(node->command_node, depth);
            print_indent(depth);
            printf("└─ARGS: ");
            for (t_command_args *arg = node->command_node->command_args; arg; arg = arg->next) {
                printf("\"%s\" ", arg->string);
            }
            printf("\n");
            break;
    }
}

// char	*get_all_path(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strlen(envp[i]) >= 5 && ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			return (envp[i] + 5);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// void	free_split(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr && arr[i] != NULL)
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }

// void	free_splits(char **cmds, char **path)
// {
// 	free_split(cmds);
// 	free_split(path);
// }

// char	*valid_command(char **cmds, char **path, char *tmp, char *full_path)
// {
// 	int	i;

// 	i = 0;
// 	while (path[i])
// 	{
// 		tmp = ft_strjoin(path[i], "/");
// 		if (!tmp)
// 			break ;
// 		full_path = ft_strjoin(tmp, cmds[0]);
// 		free(tmp);
// 		if (!full_path)
// 			break ;
// 		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
// 		{
// 			free_splits(cmds, path);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	free_splits(cmds, path);
// 	return (NULL);
// }

// char	*generate_path(char *cmd, char **envp)
// {
// 	char	**path;
// 	char	**cmds;

// 	if (!cmd || !envp)
// 		return (NULL);
// 	path = ft_split(get_all_path(envp), ':');
// 	if (!path)
// 		return (NULL);
// 	cmds = ft_split(cmd, ' ');
// 	if (!cmds)
// 	{
// 		free_split(path);
// 		return (NULL);
// 	}
// 	return (valid_command(cmds, path, NULL, NULL));
// }

// void ft_execvp(char *cmd, char **envp)
// {
// 	char	*full_path;
// 	char	**cmds;

// 	if (!cmd || !envp)
// 		exit(EXIT_FAILURE);
// 	full_path = generate_path(cmd, envp);
// 	cmds = ft_split(cmd, ' ');
// 	if (!cmds)
// 		exit(EXIT_FAILURE);
// 	if (full_path == NULL)
// 	{
// 		perror("command not found");
// 		free_split(cmds);
// 		exit(127);
// 	}
// 	if (execve(full_path, cmds, envp) == -1)
// 	{
// 		free_split(cmds);
// 		free(full_path);
// 		exit(EXIT_FAILURE);
// 	}
// 	free_split(cmds);
// 	free(full_path);
// }

// void execute_command(t_ast_node *node, char **envp, int input_fd, int output_fd);

// static void execute_pipeline(t_ast_node *node, char **envp, int input_fd) {
//     int fd[2];
//     pid_t pid;

//     if (pipe(fd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid = fork();
//     if (pid == 0) {
//         close(fd[0]);
//         dup2(input_fd, STDIN_FILENO);
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         execute_command(node->pipe_node->left, envp, STDIN_FILENO, STDOUT_FILENO);
//         exit(EXIT_SUCCESS);
//     }

//     pid = fork();
//     if (pid == 0) {
//         close(fd[1]);
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         if (node->pipe_node->right->type == AST_PIPE) {
//             execute_pipeline(node->pipe_node->right, envp, STDIN_FILENO);
//         } else {
//             execute_command(node->pipe_node->right, envp, STDIN_FILENO, STDOUT_FILENO);
//         }
//         exit(EXIT_SUCCESS);
//     }

//     close(fd[0]);
//     close(fd[1]);
//     waitpid(-1, NULL, 0);
//     waitpid(-1, NULL, 0);
// }

// void handle_redirect(t_cmd *cmd) 
// {
//     t_infile_redir *ir = cmd->infile_redir;
// 	int flags;
// 	int	fd;
//     while (ir) {
//         fd = open(ir->filename, O_RDONLY);
//         dup2(fd, STDIN_FILENO);
//         close(fd);
//         ir = ir->next;
//     }

//     t_outfile_redir *or = cmd->outfile_redir;
//     while (or) {
//         flags = O_WRONLY | O_CREAT;
//         if (or->redirection_flag == F_APPEND)
// 			flags |= O_APPEND;
// 		else
// 			flags |= O_TRUNC;
// 		fd = open(or->filename, flags, 0644);
//         dup2(fd, STDOUT_FILENO);
//         close(fd);
//         or = or->next;
//     }
// }

// void execute_command(t_ast_node *node, char **envp, int input_fd, int output_fd) {
// 	char *tmp;
// 	char *cmds;
// 	t_command_args *current;

// 	current = node->command_node->command_args;
//     pid_t pid = fork();
//     if (pid == 0) {
//         if (input_fd != STDIN_FILENO) 
// 			dup2(input_fd, STDIN_FILENO);
//         if (output_fd != STDOUT_FILENO) 
// 			dup2(output_fd, STDOUT_FILENO);
//         handle_redirect(node->command_node);
// 		cmds = "";
// 		cmds = ft_strjoin(cmds, current->string);
// 		current = current->next;
// 		while(current)
// 		{
// 			tmp = ft_strjoin(" ", current->string);
// 			cmds = ft_strjoin(cmds, tmp);
// 			current = current->next;
// 		}
// 		ft_execvp(cmds, envp);
//     } else {
//         waitpid(pid, NULL, 0);
//     }
// }

// void execute_ast(t_ast_node *node, char **envp) {
//     if (!node) return;

//     if (node->type == AST_PIPE) 
// 	{
//         execute_pipeline(node, envp, STDIN_FILENO);
//     }
// 	else
// 	{
//         execute_command(node, envp, STDIN_FILENO, STDOUT_FILENO);
//     }
// }

// int	main(int argc, char **argv, char **envp)
// {

// 	char *line = "<< EOF < infile echo hello | grep h > outfile";
//     t_token *token = input_scanner(line);
//     t_ast_node *tree = parse_tokens(&token);
//     
//     printf("\n--- AST Structure ---\n");
//     print_ast(tree, 0);
//     return 0;
// }
