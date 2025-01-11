#include "minishell.h"
//ls | grep .c | wc -l
int main()
{
    int fd[2];

    pipe(fd);
    if (fork() == 0)
    {
        close(fd[0]);//読み込みfdはlsなのでいらない
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    }
    // else {
    //     wait(NULL);
    // }
    pipe
    if (fork() == 0)
    {
        // close(fd[0]);
        dup2(fd[0], STDIN_FILENO);
        pipe(fd);
        dup2(fd[1], STDOUT_FILENO);
        execlp("grep", "grep", ".c", NULL);
    }
    //  else {
    //     wait(NULL);
    // }
    //ここでpipeを使ったら
    if (fork() == 0)
    {
        // close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    }
    // else {
    //     wait(NULL);
    // }
}