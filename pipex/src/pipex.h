#ifndef PIPEX_H
#	define PIPEX_H
#	include "../libft/libft.h"
# include "../libft/get_next_line.h"
#	include <error.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <fcntl.h>
#	include <sys/types.h>
#	include <sys/wait.h>
#endif

char	*get_all_pass(char **envp);
void	free_split(char **arr);
char	*generate_path(char *cmd, char **envp);
void	ft_execvp(char *cmd, char **envp);
void	parent_process(int *p, char **argv, char **envp);
void 	child_process(int *p, char **argv, char **envp);
