#include "../minishell.h"

void handle_sigint(int sig) {
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

int main() {
    char *input;
	t_context context;
	context.environ = map_new();
	context.last_status = 0;
  signal(SIGINT, handle_sigint);
    while (1) {
        // ユーザーにプロンプトを表示して入力を受け取る
        input = readline("minishell:)");

        if (input == NULL) { // EOF (Ctrl+D)の場合
            printf("\nExiting...\n");
            break;
        }

        if (*input) { // 入力が空でない場合
            add_history(input); // 履歴に追加
            interpret(input, &context); // 入力を解釈して実行
        }

        printf("You entered: %s\n", input);

        free(input); // readlineが動的に確保したメモリを解放
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <unistd.h>

// // SIGINT シグナルのハンドラー関数
// void handle_sigint(int sig) {
//     printf("\nCaught signal %d (SIGINT). Exiting gracefully...\n", sig);
//     exit(0);
// }

// int main() {
//     struct sigaction sa;

//     // sigaction 構造体をゼロで初期化
//     sa.sa_handler = handle_sigint;  // シグナルハンドラー関数を設定
//     sa.sa_flags = 0;  // フラグなし
//     sigemptyset(&sa.sa_mask); // 他のシグナルをブロックしない

//     // SIGINT (Ctrl+C) のハンドラーを設定
//     if (sigaction(SIGINT, &sa, NULL) == -1) {
//         perror("sigaction");
//         exit(1);
//     }

//     printf("Press Ctrl+C to trigger SIGINT...\n");

//     while (1) {
//         printf("Running...\n");
//         sleep(2);
//     }

//     return 0;
// }

