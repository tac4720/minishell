#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void execute_pipeline(char ***commands, int num_commands) {
    int i;
    int pipe_fd[2];         // パイプのファイルディスクリプタ
    int prev_pipe_fd = -1;  // 前回のパイプの読み取り端を保持
    pid_t pid;
    extern char **environ;  // 環境変数

    for (i = 0; i < num_commands; i++) {
        if (i < num_commands - 1) {
            // 次のコマンドのためにパイプを作成
            if (pipe(pipe_fd) < 0) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // 子プロセス
            if (prev_pipe_fd != -1) {
                // 前回のパイプの読み取り端を標準入力にリダイレクト
                dup2(prev_pipe_fd, STDIN_FILENO);
                close(prev_pipe_fd);
            }

            if (i < num_commands - 1) {
                // 次のパイプの書き込み端を標準出力にリダイレクト
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // パイプを全て閉じる（不要なもの）
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // コマンドのフルパスを指定する
            char *path = commands[i][0];
            execve(path, commands[i], environ);
            perror("execve");  // execveが戻った場合はエラー
            exit(EXIT_FAILURE);
        }

        // 親プロセス
        if (prev_pipe_fd != -1)
            close(prev_pipe_fd);  // 前回のパイプの読み取り端を閉じる

        if (i < num_commands - 1) {
            close(pipe_fd[1]);    // 次のパイプの書き込み端を閉じる
            prev_pipe_fd = pipe_fd[0]; // 次のパイプの読み取り端を保持
        }
    }

    // 全ての子プロセスが終了するまで待機
    for (i = 0; i < num_commands; i++) {
        wait(NULL);
    }
}

int main() {
    // コマンドリスト
    char *cmd1[] = {"/bin/ls", NULL};
    char *cmd2[] = {"/bin/grep", ".c", NULL};
    char *cmd3[] = {"/usr/bin/wc", "-l", NULL};
    char **commands[] = {cmd1, cmd2, cmd3};

    // パイプラインを実行
    execute_pipeline(commands, 3);

    return 0;
}
