#include <stdio.h>
#include "../builtin_execute/builtin.h"

int ft_env(char **args, t_context *context)
{
	t_map	*env;
	int 	i;

	env = context->environ;
	i = 0;
	if (args[2] != NULL) 
  	{
		return (1);
  	}

	while (i < TABLE_SIZE)
    {
      t_item *current = env->table[i];
      while (current)
      {
        ft_printf("%s=%s\n", current->name, current->value);
        current = current->next;
      }
		i++;
    }
	return (0);
}
