#include "minishell.h"

int main() {
    char *input;

    while (1) {
        // ユーザーにプロンプトを表示して入力を受け取る
        input = readline("minishell:)");

        if (input == NULL) { // EOF (Ctrl+D)の場合
            printf("\nExiting...\n");
            break;
        }

        if (*input) { // 入力が空でない場合
            add_history(input); // 履歴に追加
            interpret(input); // 入力を解釈して実行
        }

        printf("You entered: %s\n", input);

        free(input); // readlineが動的に確保したメモリを解放
    }

    return 0;
}
