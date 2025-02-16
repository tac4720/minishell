/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:22:31 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/16 15:57:42 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_map(t_map *map)
{
    if (map == NULL)
        return;

	t_item *item;
    for (size_t i = 0; i < TABLE_SIZE; i++)
    {
        item = map->table[i];
        while (item != NULL)
        {
            t_item *next = item->next;
            free(item->name);
            free(item->value);
            free(item);
            item = next;
        }
        map->table[i] = NULL;
    }
    free(map);
}
