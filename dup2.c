#include "minishell.h"

int main(){
    char buf[100];
    int fd_0 = open("test.txt", O_RDONLY);

    int fd_1;
    if (fork() == 0)
    {
        close(fd_1);
        dup2(fd_0, fd_1);
        // read(fd_1, buf, 100);
        // printf("%s\n", buf);
    }
    // dup2(fd_0, fd_1);
    read(fd_1, buf, 100);
    printf("%s\n", buf);
}