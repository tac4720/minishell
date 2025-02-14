#include <unistd.h>
#include "../builtin_execute/builtin.h"


int ft_export(char **args, t_context *context)
{
  t_map *env = context->environ;
  
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
    if (!isalpha(args[1][i]) && args[1][i] != '_' && args[1][i] != '=')
    {
      write(2, "export: not a valid identifier\n", 31);
      return 1;
    }
    i++;
  }
  map_put(env, args[1]);
  printf("%s\n", map_get(context->environ, args[1]));
  return 0;
}