#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "define.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/stat.h>
//tokenizer
t_token *tokenize(char *line);
int is_blank(char c);
t_token *get_token(char **s);
t_token *get_word_token(char **s);
t_token *get_operator_token(char **s);
int get_op_type(char **s);
void operator_input(t_token *node);
int check_flags(char *str);
void quote_check(char *s, int *n);
int check_redir(char **s);
t_token *input_scanner(char *line);

//parse
t_ast_node  *parse_tokens(t_token **token_list);
t_ast_node *parse_pipeline(t_token **token_list);
t_ast_node *parse_pipe(t_ast_node *left, t_token **token_list);

//parse_command.c
t_ast_node *parse_cmd(t_token **token_list);
t_ast_node *new_cmd_node(t_cmd *cmd, t_token **token_list);
void add_cmd_node(t_token **token_list, t_cmd *cmd);
void parse_args(t_token **token_list, t_cmd *cmd);

//parse_redir.c
void parse_redir(t_token **token_list, t_cmd *cmd);
void parse_file_out(t_token **token_list, t_cmd *cmd, int command_flags);
void parse_file_in(t_token **token_list, t_cmd *cmd, int command_flags);
void parse_append(t_token **token_list, t_cmd *cmd, int command_flags);
void add_infile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag);
void add_outfile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag);

//interpret関数のプロトタイプ宣言
t_ast_node	*interpret(char *line, t_context *context);
char	*make_path(const char *filename);

//readline.c
int read_tree_exec(t_context *context, t_ast_node *node);

//errors.c
void	check_open_close(char *line);
//libft
char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_printf(const char *format, ...);

//builtin
int		builtin_execute(char **args, t_context *context);

//execute.c
void execute_ast(t_ast_node *node, char **envp, t_context *ctx);
void	expand_ast(t_ast_node *node, char **envp, t_context *ctx);
void	remove_quotes(char *str);
//signal.c
void	setup_signals(t_context *ctx);
