#include "../builtin_execute/builtin.h"

int ft_unset(char **args, t_context *context)
{
  if (args[1] == NULL)
    exit(1);
  t_map *env = context->environ; //TODO:グローバル変数で定義されてる環境変数へのアクセスへ変更(変更済み)
  map_unset(env, args[1]);
  return 0; 
}
