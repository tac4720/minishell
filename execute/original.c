#include "../minishell.h"
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int pipe_process(char *cmd, char **envp);
void ft_execvp(char **cmds, char **envp, t_context *ctx);
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








#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>



