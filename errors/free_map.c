/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:22:31 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/18 20:25:57 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_map(t_map *map)
{
	t_item	*item;
	t_item	*next;
	int		i;

	i = 0;
	if (map == NULL)
		return ;
	while (i < TABLE_SIZE)
	{
		item = map->table[i];
		while (item != NULL)
		{
			next = item->next;
			free(item->name);
			free(item->value);
			free(item);
			item = next;
		}
		map->table[i] = NULL;
		i++;
	}
	free(map);
}
