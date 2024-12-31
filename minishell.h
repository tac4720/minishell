#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>

//interepret関数のプロトタイプ宣言
int	interpret(char *line);
char	*make_path(const char *filename);

//libft
char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);