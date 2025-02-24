/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:03 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/19 17:25:42 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define CMDS 1024
# include "../minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

int		pipe_process(char *cmd, char **envp);
void	ft_execvp(char **cmds, char **envp, t_context *ctx);
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
void	remove_quotes(char *str);
void	expand(t_ast_node *node, t_context *ctx);
void	handle_heredoc(t_infile_redir *ir);
void	handle_input_redirect(t_infile_redir *ir);
void	handle_output_redirect(t_outfile_redir *or);
void	handle_redirect(t_cmd *cmd);
int		count_args(t_ast_node *node);
char	**create_cmds(t_ast_node *node);
int		is_string_empty(const char *str);
void	free_commands(char **cmds);
char	**remove_empty_commands(char **cmds);
void	run_command(t_ast_node *node, int input_fd,
			int output_fd, t_context *ctx);
void	execute_command(t_ast_node *node, int input_fd,
			int output_fd, t_context *ctx);
void	reverse_commands(t_ast_node **cmds, int count);
void	store_commands(t_ast_node *node, t_ast_node **cmds, int *count);
void	child_process(t_ast_node *cmd, int in_fd, int *pipe_fd,
			t_context *ctx);
void	info_set(t_ast_node *node, t_ast_node **cmds, t_exec_info *info,
			t_context *ctx);
void	parent_process(int *in_fd, int *pipe_fd, int i, int count);
void	execute_pipeline(t_ast_node *node, char **envp, int input_fd,
			t_context *ctx);
void	expand_ast(t_ast_node *node, char **envp, t_context *ctx);
void	execute_ast(t_ast_node *node, char **envp, t_context *ctx);
char	*get_all_path(char **envp);
void	free_split(char **arr);
void	free_splits(char **cmds, char **path);
char	*valid_command(char **cmds, char **path, char *tmp, char *full_path);
char	*generate_path(char *cmd, char **envp, t_context *ctx);
void	is_dir(const char *cmd);
int		check_other(char **args, t_context *ctx, char **envp);
void	ft_execvp(char **cmds, char **envp, t_context *ctx);
int		builin_execute_p(char **args, t_context *context);
int		is_builtin(char *str);
#endif
