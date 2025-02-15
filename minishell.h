#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "define.h"

//tokenizer
t_token *tokenize(char *line);
int is_blank(char c);
t_token *get_token(char **s, t_context *context);
t_token *get_word_token(char **s, t_context *context);
t_token *get_operator_token(char **s, t_context *context);
int get_op_type(char **s);
void operator_input(t_token *node);
int check_flags(char *str);
void quote_check(char *s, int *n);
int check_redir(char **s);
t_token *input_scanner(char *line, t_context *context);

//parse
t_ast_node  *parse_tokens(t_token **token_list, t_context *context);
t_ast_node *parse_pipeline(t_token **token_list, t_context *context);
t_ast_node *parse_pipe(t_ast_node *left, t_token **token_list, t_context *context);

//parse_command.c
t_ast_node *parse_cmd(t_token **token_list, t_context *context);
t_ast_node *new_cmd_node(t_cmd *cmd, t_token **token_list, t_context *context);
void add_cmd_node(t_token **token_list, t_cmd *cmd, t_context *context);
void parse_args(t_token **token_list, t_cmd *cmd, t_context *context);

//parse_redir.c
void parse_redir(t_token **token_list, t_cmd *cmd, t_context *context);
void parse_file_out(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context);
void parse_file_in(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context);
void parse_append(t_token **token_list, t_cmd *cmd, int command_flags, t_context *context);
void add_infile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag, t_context *context);
void add_outfile_redir_node(t_token **token_list, t_cmd *cmd, int command_flag, t_context *context);

//interpret関数のプロトタイプ宣言
t_ast_node	*interpret(char *line, t_context *context);
char	*make_path(const char *filename);

//readline.c
int read_tree_exec(t_context *context, t_ast_node *node);

//errors.c
void	check_open_close(char *line);
void malloc_error(t_context *context);
void free_tokens(t_token *token_list);
void error_in_parse(t_context *context);
//libft
char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_printf(const char *format, ...);

//builtin
int		builtin_execute(char *line, t_context *context);


