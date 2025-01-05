#include "../../minishell.h"
#include "../../environ/environ.h"

int ft_unset(char **args)
{
  if (args[1] == NULL)
    exit(1);
  t_map *dummy = NULL; //TODO:グローバル変数で定義されてる環境変数へのアクセスへ変更
  map_unset(dummy, args[1]);
  return 0; 
}
