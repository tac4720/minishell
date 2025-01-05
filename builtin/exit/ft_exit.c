#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "../builtin_execute/builtin.h"
//TODO: 最後に使用したコマンドのステータスを保存表示
//TODO: カスタムperrorを使用してエラーメッセージを表示
//TODO: エラーコードの数字が正しいか？大きすぎるエラーコードが渡された場合
bool is_numeric(const char *str) {
    if (*str == '+' || *str == '-')
        str++;
    if (!(*str >= '0' && *str <= '9'))
        return false;
    while (*str) {
        if (!(*str >= '0' && *str <= '9'))
            return false;
        str++;
    }
    return true;
}

int ft_exit(char **args, t_context *context) 
{
    long status;
    char *endptr;

  if (args[1] == NULL) 
  {
    exit(context->last_status);
  } 
  else if (args[2] != NULL) 
  {
    write(2, "exit: too many arguments\n", 26);
    exit (1);
  }
  if (!is_numeric(args[1])) 
  {
      write(2, "exit: numeric argument required\n", 33);
      exit(255);
  }
  errno = 0;
  status = strtol(args[1], &endptr, 10);
  if (errno == ERANGE || *endptr != '\0') 
  {
      write(2, "exit: numeric argument required\n", 33);
      exit(255);
  }
    exit((unsigned char)status);
}

// int main(int argc, char **argv) {
//     int last_status = 0; // 最後のコマンドのステータス（仮定）
//     ft_exit(argv, last_status);
//     return 0;
// }

