#include "minishell.h"

int main()
{
    char *input;
	t_context context;
	context.environ = map_new();
	context.last_status = 0;

    while (1) {
        // ユーザーにプロンプトを表示して入力を受け取る
        input = readline("minishell:)");
        if (input == NULL) { // EOF (Ctrl+D)の場合
            printf("\nExiting...\n");
            break;
        }
        if (*input) { // 入力が空でない場合
            add_history(input); // 履歴に追加
            (&context)->tree = interpret(input, &context); // 入力を解釈
            // read_tree_exec(&context, (&context)->tree);//実行
        }
        // printf("You entered: %s\n", input);
        // free(input); // readlineが動的に確保したメモリを解放
    }

    return 0;
}
