#include "pipex.h"

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

void    here_doc(char *limiter, int fd)
{
    char *line = NULL;
    
    while (1)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
}

int    here_doc_process(char **argv)
{
    int     fd[2];
    pid_t   pid;

    if (pipe(fd) == -1)
        return (1);
    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        close(fd[0]);
        here_doc(argv[2], fd[1]);
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);
    waitpid(pid, NULL, 0);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    return (0);
}

int    main(int argc, char **argv, char **envp)
{
    int i;
    int outfile;

    if (argc < 5)
        return (1);
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        if (argc < 6)
            return (1);
        outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        here_doc_process(argv);
        i = 3;
    }
    else
    {
        int infile = open(argv[1], O_RDONLY);
        outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (infile == -1 || outfile == -1)
            return (1);
        dup2(infile, STDIN_FILENO);
        close(infile);
        i = 2;
    }
    while (i < argc - 2)
    {
        pipe_process(argv[i], envp);
        i++;
    }
    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    ft_execvp(argv[i], envp);
    return (1);
}
