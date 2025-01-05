#include <unistd.h>
#include "../builtin_execute/builtin.h"
//TODO: 引数が空の場合、環境変数を全て出力するが、その表示形式がbashと違う
//TODO: 環境変数へのアクセスが現在はダミーを使っている (変更済み)

int ft_export(char **args, t_context *context)
{
  t_map *env = context->environ; //TODO:
  
  if (args[1] == NULL)
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      t_item *current = env->table[i];
      while (current)
      {
        printf("declare -x %s=%s\n", current->name, current->value);
        current = current->next;
      }
    }
  }
  int i = 0;
  while (args[1][i])
  {
    if (!isalpha(args[1][i]) && args[1][i] != '_')
    {
      write(2, "export: not a valid identifier\n", 31);
      return 1;
    }
    i++;
  }
  map_put(env, args[1]);
  return 0;
}
