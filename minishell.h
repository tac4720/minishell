#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "environ/environ.h"

typedef enum {
    TK_WORD,
    TK_EOF,
} TokenKind;

typedef struct s_token t_token;

struct s_token {
    char    *word;
    TokenKind kind;
    t_token *next;
};



typedef struct s_context{
	int last_status;
	t_map *environ;	
} t_context; 

//interepret関数のプロトタイプ宣言
int	interpret(char *line, t_context *context);
char	*make_path(const char *filename);

//libft
char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);

//builtin
int		builtin_execute(char **args, t_context *context);

t_token *tokenize(char *line);
