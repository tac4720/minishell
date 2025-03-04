/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:34 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:27 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char	*map_get(t_map *map, const char *name)
{
	size_t	index;
	t_item	*current;

	if (!map || !name)
		return (NULL);
	index = hash_function(name);
	current = map->table[index];
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	map_set_no_value(t_map *map, const char *string)
{
	return (map_set(map, string, "@"));
}

int	map_put(t_map *map, const char *string)
{
	char	*equal_pos;
	char	*name;
	char	*value;
	int		result;

	equal_pos = ft_strchr(string, '=');
	if (!equal_pos)
		return (map_set_no_value(map, string));
	name = ft_substr(string, 0, equal_pos - string);
	value = ft_strdup(equal_pos + 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (-1);
	}
	result = map_set(map, name, value);
	free(name);
	free(value);
	return (result);
}

int	map_set(t_map *map, const char *name, const char *value)
{
	size_t	index;
	t_item	*current;

	if (!map || !name)
		return (-1);
	index = hash_function(name);
	current = map->table[index];
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (current->value)
				return (0);
			else
				return (-1);
		}
		current = current->next;
	}
	return (add_new_item(map, index, name, value));
}
