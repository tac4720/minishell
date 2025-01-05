#include <unistd.h>
#include <string.h>
#include <stdbool.h>

//TODO: エラー処理をもっと厳しくする。bash準拠のエラーメッセージを表示する。
int ft_echo(char **args)
{
  size_t i = 1;
  bool flag = false; 

  if (args[i] && strcmp(args[i], "-n") == 0)
  {
    flag = true;
    i++;
  }
  while (args[i] != NULL)
  {
    write(1, args[i], strlen(args[i]));
    if (args[i + 1] != NULL)
      write(1, " ", 1);
    i++;
  }
  if (flag == false)
    write(1, "\n", 1);
  return 0;
}

// int main(int argc, char **argv)
// {
//   ft_echo(argv);
//   return 0;
// }
