#include "../../environ/environ.h"
#include <stdio.h>

//TODO: ダミー変数をグローバル変数で定義された環境変数へのアクセスへ変更
//TODO: 表示形式がbashと一致しているか確認

int ft_env(char **args)
{
	t_map *dummy = NULL;
	int i = 0;

	if (args[2] != NULL) 
  	{
		return (1);
  	}

	while (i < TABLE_SIZE)
    {
      t_item *current = dummy->table[i];
      while (current)
      {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
      }
		i++;
    }
	return (0);
}
