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
t_token *get_token(char **s);
t_token *get_word_token(char **s);
t_input *get_word(char **s);
t_token *get_operator_token(char **s);
int get_op_type(char **s);
void operator_input(t_token *node);
int check_flags(char *str);
void check_quotes(t_input *current, int *i);
void quote_check(char *s, int *n);
int check_redir(char **s);
t_token *input_scanner(char *line);

//parse
t_ast_node  *parse_line(t_token **token_list);
t_ast_node *parse_cmd(t_token **token_list);
t_ast_node *parse_pipeline(t_token **token_list);
t_ast_node *parse_pipe(t_ast_node *left, t_token **token_list);

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
//builtin
int		builtin_execute(char *line, t_context *context);


