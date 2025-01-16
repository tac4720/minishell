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

typedef struct s_input
{
	int				flag;
	char			*input;
	struct s_input	*next;
	struct s_input	*prev;
} t_input;

typedef struct s_token {
    t_token_type type;
    t_input *cmd;
    struct s_token *next;
    struct s_token *prev;
} t_token;




//tokenizer.c
t_token *tokenize(char *line);
int is_blank(char c);


//interepret関数のプロトタイプ宣言
int	interpret(char *line, t_context *context);
char	*make_path(const char *filename);
t_token *get_word_token(char **s);
t_input *get_word(char **s);
t_token *get_operator_token(char **s);
int get_op_type(char **s);
void operator_input(t_token *node);
t_token *get_token(char **s);
int check_flags(t_input *current);
void check_quotes(t_input *current, int *i);
void quote_check(char *s, int *n);
int check_redir(char **s);
t_token *input_scanner(char *line);

//libft
char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//builtin
int		builtin_execute(char *line, t_context *context);


