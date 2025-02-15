#include "environ.h"

t_item	*item_new(char *name, char *value)
{
	t_item	*item;

	item = (t_item *)ft_calloc(1, sizeof(t_item));
	if (!item)
		return (NULL);
	item->name = ft_strdup(name);
	item->value = ft_strdup(value);
	if (!item->name || !item->value)
	{
		free(item->name);
		free(item->value);
		free(item);
		return (NULL);
	}
	item->next = NULL;
	return (item);
}


void	free_item(t_item *item)
{
	free(item->name);
	free(item->value);
	free(item);
}
