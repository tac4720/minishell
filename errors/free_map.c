/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:22:31 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/16 13:25:27 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_map(t_map *map)//仮
{
	int i;
	t_item *tmp;
	t_item *next;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = map->table[i];
		while (tmp != NULL)
		{
			next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			tmp = next;
		}
		i++;
	}
	free(map);
}