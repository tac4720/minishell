
#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int pipe_process(char *cmd, char **envp);
void ft_execvp(char *cmd, char **envp);
void here_doc(const char *limiter, int fd);
void print_ast(t_ast_node *node, int depth);
void	init_context(t_context *ctx, char **envp);


typedef struct s_exec_info
{
	int		count;
	int		i;
	char	**envp;
}	t_exec_info;


static char	*join_and_free(char *s1, char *s2, int free_s2)
{
	char	*result;
	char	*tmp;

	tmp = s1;
	result = ft_strjoin(s1, s2);
	free(tmp);
	if (free_s2)
		free(s2);
	return (result);
}

static char	*expand_status(const char *str, int *i, char *result, t_context *ctx)
{
	char	*expand_str;

	if (str[*i + 1] == '?')
	{
		expand_str = ft_itoa(ctx->last_status);
		result = join_and_free(result, expand_str, 1);
		*i += 2;
	}
	return (result);
}

static char	*get_env_value(const char *str, int *i)
{
	char	*var_name;
	int		start;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static char	*expand_env_var(const char *str, int *i, char *result, t_context *ctx)
{
	char	*var_name;
	char	*expand_str;

	(*i)++;
	var_name = get_env_value(str, i);
	expand_str = map_get(ctx->environ, var_name);
	free(var_name);
	if (expand_str)
	{
		result = join_and_free(result , expand_str, 0);
	}
	else 
	{
		result = join_and_free(result, "", 0);
	}
	return (result);
}

static char	*expand_normal_str(const char *str, int *i, char *result)
{
	char	*tmp;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	result = join_and_free(result, tmp, 1);
	return (result);
}

char	*expand_helper(const char *str, t_context *ctx)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				result = expand_status(str, &i, result, ctx);
			else
				result = expand_env_var(str, &i, result, ctx);
			continue ;
		}
		result = expand_normal_str(str, &i, result);
	}
	return (result);
}




void	expand(t_ast_node *node, t_context *ctx)
{
	t_command_args *current;
	char *expand_str;
	char *tmp;

	current = node->command_node->command_args;
	while (current)
	{
		current->string = expand_helper(current->string, ctx);
		current = current->next;
	}
}

void handle_redirect(t_cmd *cmd) {
    t_infile_redir *ir = cmd->infile_redir;
    int flags;
    int fd;
    while (ir) {
        if (ir->redirection_flag == F_HEREDOC) {
            fd = open(ir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            here_doc(ir->filename, fd);
            close(fd);

            fd = open(ir->filename, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            unlink(ir->filename);
            ir = ir->next;
            continue;
        }
        fd = open(ir->filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
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
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        or = or->next;
    }
}

void run_command(t_ast_node *node, char **envp, int input_fd, int output_fd) {
    if (input_fd != STDIN_FILENO) {
         dup2(input_fd, STDIN_FILENO);
         close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
         dup2(output_fd, STDOUT_FILENO);
         close(output_fd);
    }
    handle_redirect(node->command_node);

    t_command_args *current = node->command_node->command_args;
    char *cmds = ft_strdup(current->string);
    current = current->next;
    char *tmp;
    while (current) {
         tmp = ft_strjoin(cmds, " ");
         free(cmds);
         cmds = ft_strjoin(tmp, current->string);
         free(tmp);
         current = current->next;
    }
    ft_execvp(cmds, envp);
    free(cmds);
    exit(EXIT_FAILURE);
}

void execute_command(t_ast_node *node, char **envp, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid == 0) {
         run_command(node, envp, input_fd, output_fd);
         exit(EXIT_FAILURE);
    } else {
         waitpid(pid, NULL, 0);
    }
}


static void	reverse_commands(t_ast_node **cmds, int count)
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

static void	store_commands(t_ast_node *node, t_ast_node **cmds, int *count)
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

static void	child_process(t_ast_node *cmd, int in_fd, int *pipe_fd,
		t_exec_info *info)
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
	run_command(cmd, info->envp, STDIN_FILENO, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

static void	parent_process(int *in_fd, int *pipe_fd, int i, int count)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (i < count - 1)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

void	execute_pipeline(t_ast_node *node, char **envp, int input_fd)
{
	t_ast_node	*cmds[256];
	t_exec_info	info;
	int			pipe_fd[2];
	int			in_fd;
	pid_t		pid;

	info.count = 0;
	info.envp = envp;
	store_commands(node, cmds, &info.count);
	reverse_commands(cmds, info.count);
	in_fd = input_fd;
	info.i = 0;
	while (info.i < info.count)
	{
		if (info.i < info.count - 1 && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
			child_process(cmds[info.i], in_fd, pipe_fd, &info);
		parent_process(&in_fd, pipe_fd, info.i, info.count);
		info.i++;
	}
	while (waitpid(-1, NULL, 0) > 0);
}

// void execute_pipeline(t_ast_node *node, char **envp, int input_fd) {
//     t_ast_node *cmds[256];
//     int count = 0;
//     
//     while (node && node->type == AST_PIPE) {
//          cmds[count++] = node->pipe_node->right;
//          node = node->pipe_node->left;
//     }
//     if (node)
//          cmds[count++] = node;
//     
//     for (int i = 0; i < count/2; i++) {
//          t_ast_node *temp = cmds[i];
//          cmds[i] = cmds[count - 1 - i];
//          cmds[count - 1 - i] = temp;
//     }
//     
//     int in_fd = input_fd;
//     int pipe_fd[2];
//     pid_t pid;
//     
//     for (int i = 0; i < count; i++) {
//          if (i < count - 1) {
//               if (pipe(pipe_fd) == -1) {
//                    perror("pipe");
//                    exit(EXIT_FAILURE);
//               }
//          }
//          
//          pid = fork();
//          if (pid == 0) {
//               if (in_fd != STDIN_FILENO) {
//                    dup2(in_fd, STDIN_FILENO);
//                    close(in_fd);
//               }
//               if (i < count - 1) {
//                    dup2(pipe_fd[1], STDOUT_FILENO);
//                    close(pipe_fd[0]);
//                    close(pipe_fd[1]);
//               }
//               run_command(cmds[i], envp, STDIN_FILENO, STDOUT_FILENO);
//               exit(EXIT_FAILURE);
//          }
//          
//          if (in_fd != STDIN_FILENO)
//               close(in_fd);
//          if (i < count - 1) {
//               close(pipe_fd[1]);
//               in_fd = pipe_fd[0];
//          }
//     }
//     
//     int status;
//     while (waitpid(-1, &status, 0) > 0);
// }

// void	expand_helper(char *str, t_context *ctx)
// {
// 	int i;
// 	int start;
// 	char *expand_str;
// 	char *tmp;

// 	i = 0;
// 	start = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			if (str[i + 1] == '?')
// 			{
// 				expand_str = ft_strjoin(expand_str,ft_itoa(ctx->last_status));
// 				i++;
// 				start = i;
// 				continue;
// 			}
// 			tmp = ft_substr(str, start, i);
// 			expand_str = ft_strjoin(expand_str, tmp);
// 			while(str[i] != '$' && str[i] != '\0')
// 			{
// 				i++;
// 			}
// 			tmp = ft_substr(str, start, i);
// 			expand_str = ft_strjoin(expand_str, map_get(ctx->environ, tmp));
// 			start = i;
// 			continue;
// 		}
// 		i++;
// 	}
// }

void	expand_ast(t_ast_node *node, char **envp, t_context *ctx)
{
	if (!node) return;
	if (node->type == AST_PIPE)
	{
		expand_ast(node->pipe_node->left, envp, ctx);
		expand_ast(node->pipe_node->right, envp, ctx);
	}
	else
	{
		expand(node, ctx);
	}
}

void execute_ast(t_ast_node *node, char **envp, t_context *ctx) 
{
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

// int main(int argc, char **argv, char **envp) {
//     char *line;
//     t_token *token;
//     t_ast_node *tree;
//     
//     while (1) {
//          line = readline("minishell:");
//          if (!line) {
//               printf("exit\n");
//               break;
//          }
//          token = input_scanner(line);
//          if (!token) {
//               free(line);
//               continue;
//          }
//          tree = parse_tokens(&token);
//          if (!tree) {
//               free(line);
//               continue;
//          }
//          execute_ast(tree, envp);
// 		print_ast(tree, 0);
//          free(line);
//     }
//     return 0;
// }
static volatile sig_atomic_t g_sigint = 0; 

int	main(int argc, char **argv, char **envp)
{
    t_context	ctx;
    char		*input;
    char *line;
    t_token *token;
    t_ast_node *tree;

	(void)argc;
    (void)argv;
    init_context(&ctx, envp);
	ctx.environ = map_new();
	// printf("%s\n", map_get(ctx.environ, "PWD"));
    while (1)
    {
        if (g_sigint)
        {
            rl_redisplay();
            g_sigint = 0;
        }

        input = readline("minishell:)");

        if (input == NULL)  // EOF (Ctrl+D)の場合
        {
            printf("\nExiting...\n");
            break;
        }
        if (*input)
        {
            add_history(input);
			token = input_scanner(input);
			tree = parse_tokens(&token);
			expand_ast(tree, envp, &ctx);
			execute_ast(tree, envp, &ctx);
			print_ast(tree, 0);
            // interpret(input, &ctx); // 入力を解釈して実行
        }
        free(input);
    }
    return (ctx.last_status);
}

