/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:37 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 18:54:57 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static char	*process_unset_key(const char *name)
{
	char	*key;
	char	*eq_pos;

	key = ft_strtrim(name, "\"'");
	if (!key)
		return (NULL);
	eq_pos = ft_strchr(key, '=');
	if (eq_pos)
		*eq_pos = '\0';
	return (key);
}

static t_item	**find_item_ptr(t_map *map, const char *key, unsigned int index)
{
	t_item	*current;
	t_item	**prev_ptr;

	current = map->table[index];
	prev_ptr = &map->table[index];
	while (current)
	{
		if (ft_strncmp(current->name, key, ft_strlen(key) + 1) == 0)
			return (prev_ptr);
		prev_ptr = &current->next;
		current = current->next;
	}
	return (NULL);
}

int	map_unset(t_map *map, const char *name)
{
	unsigned int	index;
	char			*key;
	t_item			**prev_ptr;
	t_item			*to_remove;

	if (!map || !name)
		return (-1);
	key = process_unset_key(name);
	if (!key)
		return (-1);
	index = hash_function(key);
	prev_ptr = find_item_ptr(map, key, index);
	if (!prev_ptr)
	{
		free(key);
		return (-1);
	}
	to_remove = *prev_ptr;
	*prev_ptr = to_remove->next;
	free_item(to_remove);
	free(key);
	return (0);
}
