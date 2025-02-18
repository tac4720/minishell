/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:26 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 12:09:43 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	add_new_item(t_map *map, size_t index, const char *name, const char *value)
{
	t_item	*new_item;

	new_item = item_new((char *)name, (char *)value);
	if (!new_item)
		return (-1);
	new_item->next = map->table[index];
	map->table[index] = new_item;
	return (0);
}

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
