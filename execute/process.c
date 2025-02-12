#include "../minishell.h"

void ft_execvp(char *cmd, char **envp);

void    c_process(int *p, char *cmd, char **envp)
{
    dup2(p[1], STDOUT_FILENO);
    close(p[0]);
    ft_execvp(cmd, envp);
}

void    p_process(int *p)
{
    dup2(p[0], STDIN_FILENO);
    close(p[1]);
}

int    pipe_process(char *cmd, char **envp)
{
    int        fd[2];
    pid_t    pid;
    if (pipe(fd) == -1)
        return (EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0)
    {
        c_process(fd, cmd, envp);
    }
    else
    {
        waitpid(pid, NULL, 0);
        p_process(fd);
    }
    return (EXIT_SUCCESS);
}

