#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // "PATH" 環境変数を取得
    char *path = getenv("USER");

    if (path) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH 環境変数が見つかりません。\n");
    }

    return 0;
}
