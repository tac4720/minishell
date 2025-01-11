#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd;

    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fork() == 0) {
        // fd = open("test.txt", O_WRONLY);
    write(fd, "Hello, World!\n", 14);
    close(fd);
    }
    else {
        wait(NULL);
 


    }

    return 0;
}
