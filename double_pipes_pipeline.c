#include "minishell.h"
//ls | grep .c | wc -l
int main()
{
    int fd_x[2];
    int fd_y[2];

    pipe(fd_x);
    if (fork() == 0)
    {
        close(fd_x[0]);//読み込みfdはlsなのでいらない
        dup2(fd_x[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    }

    close(fd_x[1]);

    pipe(fd_y);
    if (fork() == 0)
    {
        // close(fd[0]);
        dup2(fd_x[0], STDIN_FILENO);
        close(fd_y[0]);
        dup2(fd_y[1], STDOUT_FILENO);
        execlp("grep", "grep", ".c", NULL);
    }
    close(fd_y[1]);
    if (fork() == 0)
    {
        // close(fd_y[1]);
        dup2(fd_y[0], STDIN_FILENO);
        execlp("wc", "wc", NULL);
    }

    //wc以外を試してみる？
}