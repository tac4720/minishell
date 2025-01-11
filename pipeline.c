#include "minishell.h"
int main()
{
    int fd[2];
    int i = 0;

    pipe(fd);
    while (i <5)
    {
        if (fork() == 0)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            execlp("ls", "ls", NULL);
        }
        printf("parent\n");
        i++;
    }

}