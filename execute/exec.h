#ifndef EXECUTION_H
#define EXECUTION_H

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_exec_info
{
	int		count;
	int		i;
	char	**envp;
}	t_exec_info;


int		pipe_process(char *cmd, char **envp);
void	ft_execvp(char *cmd, char **envp, t_context *ctx);
void	here_doc(const char *limiter, int fd);
void	print_ast(t_ast_node *node, int depth);
void	init_context(t_context *ctx, char **envp);
void	setup_signals(t_context *ctx);
char	*join_and_free(char *s1, char *s2, int free_s2);
char	*expand_status(const char *str, int *i, char *result, t_context *ctx);
char	*get_env_value(const char *str, int *i);
char	*expand_env_var(const char *str, int *i, char *result, t_context *ctx);
char	*expand_normal_str(const char *str, int *i, char *result);
char	*expand_helper(const char *str, t_context *ctx);
void	expand(t_ast_node *node, t_context *ctx);
void	handle_heredoc(t_infile_redir *ir);
void	handle_input_redirect(t_infile_redir *ir);
void	handle_output_redirect(t_outfile_redir *or);
void	handle_redirect(t_cmd *cmd);
void	run_command(t_ast_node *node, char **envp, int input_fd, int output_fd, t_context *ctx);
void	execute_command(t_ast_node *node, char **envp, int input_fd, int output_fd, t_context *ctx);
void	reverse_commands(t_ast_node **cmds, int count);
void	store_commands(t_ast_node *node, t_ast_node **cmds, int *count);
void	child_process(t_ast_node *cmd, int in_fd, int *pipe_fd, t_exec_info *info, t_context *ctx);
void	parent_process(int *in_fd, int *pipe_fd, int i, int count);
void	execute_pipeline(t_ast_node *node, char **envp, int input_fd, t_context *ctx);
void	expand_ast(t_ast_node *node, char **envp, t_context *ctx);
void	execute_ast(t_ast_node *node, char **envp, t_context *ctx);
char	*get_all_path(char **envp);
void	free_split(char **arr);
void	free_splits(char **cmds, char **path);
char	*valid_command(char **cmds, char **path, char *tmp, char *full_path);
char	*generate_path(char *cmd, char **envp);
void	is_dir(const char *cmd);
int		check_other(char **args, t_context *ctx, char **envp);
void	execute_command(char *full_path, char **cmds, char **envp, t_context *ctx);
void	ft_execvp(char *cmd, char **envp, t_context *ctx);
#endif
