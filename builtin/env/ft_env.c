#include <stdio.h>
#include "../builtin_execute/builtin.h"
//TODO: ダミー変数をグローバル変数で定義された環境変数へのアクセスへ変更
//TODO: 表示形式がbashと一致しているか確認

int ft_env(char **args, t_context *context)
{
	t_map *env = context->environ;
	int i = 0;

	if (args[2] != NULL) 
  	{
		return (1);
  	}

	while (i < TABLE_SIZE)
    {
      t_item *current = env->table[i];
      while (current)
      {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
      }
		i++;
    }
	return (0);
}
