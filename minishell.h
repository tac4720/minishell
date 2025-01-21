#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "environ/environ.h"

# define OPERATORS	"<>|"

typedef struct s_context{
	int last_status;
	t_map *environ;	
	int is_in_pipeline;
} t_context; 

typedef enum e_token_type
{
	HEREDOC,
	APPEND,
	FILE_IN,
	FILE_OUT,
	ENV_PARAM,
	PIPE_OP,
	WORD,
	ERROR
}	t_token_type;

typedef struct s_input
{
	int				flag;
	char			*input;
	struct s_input	*next;
	struct s_input	*prev;
} t_input;

typedef struct s_cmd
{
	int n;
	int in_fd;
	int out_fd;
	t_input *name;
	t_input *args;
} t_cmd;

typedef enum e_ast_node_type
{
	AST_PIPE,
	AST_COMMAND
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type	type;
	int				in_fd;
	int 			out_fd;
	void 			*node;
} t_ast_node;

typedef struct s_pipe
{
	int in_fd;
	int out_fd;
	t_ast_node *left;
	t_ast_node *right;
} t_pipe;



typedef enum e_flags
{
	F_DOLLAR			= 1 << 0,
	F_SQUOTES			= 1 << 1,
	F_DQUOTES			= 1 << 2,
	F_ASSIGNMENT		= 1 << 3,
	F_MUL_DOLLAR		= 1 << 4,
	F_EXPANDED			= 1 << 5,
	F_DEL_QUOTES		= 1 << 6
}	t_flags;

typedef struct s_token {
    t_token_type type;
    t_input *cmd;
    struct s_token *next;
    struct s_token *prev;
} t_token;

//tokenizer
t_token *tokenize(char *line);
int is_blank(char c);
t_token *get_token(char **s);
t_token *get_word_token(char **s);
t_input *get_word(char **s);
t_token *get_operator_token(char **s);
int get_op_type(char **s);
void operator_input(t_token *node);
int check_flags(t_input *current);
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

//libft
char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//builtin
int		builtin_execute(char *line, t_context *context);


