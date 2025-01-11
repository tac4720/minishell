#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd_x[2];
    int fd_y[2];

    pipe(fd_x);
    if (fork() == 0) {
        close(fd_x[0]);
        dup2(fd_x[1], STDOUT_FILENO);
        close(fd_x[1]);
        execlp("ls", "ls", NULL);
    }
    close(fd_x[1]);  // 親プロセスは書き込み側を閉じる

    pipe(fd_y);
    if (fork() == 0) {
        dup2(fd_x[0], STDIN_FILENO);
        close(fd_x[0]);
        dup2(fd_y[1], STDOUT_FILENO);
        close(fd_y[0]);
        close(fd_y[1]);
        execlp("grep", "grep", ".c", NULL);
    }
    close(fd_x[0]);  // 親プロセスはfd_xを完全に閉じる
    close(fd_y[1]);  // 親プロセスは書き込み側を閉じる

    if (fork() == 0) {
        dup2(fd_y[0], STDIN_FILENO);
        close(fd_y[0]);
        execlp("head", "head", "-n", "5", NULL);
    }
    close(fd_y[0]);  // 親プロセスは残りのfdを閉じる

    // // 全ての子プロセスの終了を待つ
    // wait(NULL);
    // wait(NULL);
    // wait(NULL);

    return 0;
}