
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char write_msg[] = "Hello, Pipe!";
    char read_msg[100];

    // パイプを作成
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // パイプにデータを書き込む
    write(pipefd[1], write_msg, strlen(write_msg) + 1);

    // パイプからデータを読み取る
    read(pipefd[0], read_msg, 3);
    read(pipefd[0], read_msg, 3);


    printf("Received message: %s\n", read_msg);

    // ファイルディスクリプタを閉じる
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
