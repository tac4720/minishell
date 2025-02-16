#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int pipe_process(char *cmd, char **envp);
void ft_execvp(char *cmd, char **envp, t_context *ctx);
void here_doc(const char *limiter, int fd);
void print_ast(t_ast_node *node, int depth);
void	init_context(t_context *ctx, char **envp);
void	setup_signals(t_context *ctx);


typedef struct s_exec_info
{
	int		count;
	int		i;
	char	**envp;
}	t_exec_info;

 char	*join_and_free(char *s1, char *s2, int free_s2)
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

 char	*expand_status(const char *str, int *i, char *result, t_context *ctx)
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

 char	*get_env_value(const char *str, int *i)
{
	char	*var_name;
	int		start;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

 char	*expand_env_var(const char *str, int *i, char *result, t_context *ctx)
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

 char	*expand_normal_str(const char *str, int *i, char *result)
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
			if (ft_strlen(str) == 1)
			{
				result = ft_strdup("$");
				break;
			}
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

void	remove_quotes(char *str)
{
	int		i = 0;
	int		j = 0;
	char	quote = '\0';

	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (quote == '\0')
			{
				quote = str[i];
				i++;
				continue;
			}
			else if (str[i] == quote)
			{
				quote = '\0';
				i++;
				continue;
			}
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	expand(t_ast_node *node, t_context *ctx)
{
	t_command_args *current;
	char *expand_str;
	char *tmp;

	current = node->command_node->command_args;
	while (current)
	{
		// printf("%i\n", current->flag);
		if (current->flag & (F_DOLLAR_IN_DQUOTES | F_SQUOTES | F_DQUOTES))
			remove_quotes(current->string);
		if (current->flag != F_SQUOTES)
		{
			current->string = expand_helper(current->string, ctx);
		}
		current = current->next;
	}
}


 void handle_heredoc(t_infile_redir *ir)
{
    int fd;

    fd = open(ir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    here_doc(ir->filename, fd);
    close(fd);
    fd = open(ir->filename, O_RDONLY);
    if (fd == -1)
    {
		exit (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    unlink(ir->filename);
}

 void handle_input_redirect(t_infile_redir *ir)
{
    int fd;

    while (ir)
    {
        if (ir->redirection_flag == F_HEREDOC)
        {
            handle_heredoc(ir);
            ir = ir->next;
            continue;
        }
		remove_quotes(ir->filename);
        fd = open(ir->filename, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        ir = ir->next;
    }
}

 void handle_output_redirect(t_outfile_redir *or)
{
    int flags;
    int fd;

    while (or)
    {
        flags = O_WRONLY | O_CREAT;
        if (or->redirection_flag == F_APPEND)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
		remove_quotes(or->filename);
        fd = open(or->filename, flags, 0644);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        or = or->next;
    }
}

void handle_redirect(t_cmd *cmd)
{
	// if (cmd->infile_redir->redirection_flag == FILE_IN ||
	// 	cmd->outfile_redir->redirection_flag == FILE_OUT ||
	// 	cmd->outfile_redir->redirection_flag == APPEND
	// )
	// {
	// }

    handle_input_redirect(cmd->infile_redir);
    handle_output_redirect(cmd->outfile_redir);
}

void run_command(t_ast_node *node, char **envp, int input_fd, int output_fd, t_context *ctx)
{
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
	ft_execvp(cmds, envp, ctx);
	free(cmds);
	exit(0);
}

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

void	execute_pipeline(t_ast_node *node, char **envp, int input_fd, t_context *ctx)
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
			child_process(cmds[info.i], in_fd, pipe_fd, &info, ctx);
		parent_process(&in_fd, pipe_fd, info.i, info.count);
		info.i++;
	}
	while (waitpid(-1, &(ctx->last_status), 0) > 0)
    	ctx->last_status = WEXITSTATUS(ctx->last_status);
}

void	expand_ast(t_ast_node *node, char **envp, t_context *ctx)
{
	if (!node)
		return ;
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
	if (!node)
		return ;
	if (node->type == AST_PIPE) 
	{
		execute_pipeline(node, envp, STDIN_FILENO, ctx);
	}
	else
	{
		execute_command(node, envp, STDIN_FILENO, STDOUT_FILENO, ctx);
	}
}

