#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "environ.h"
#include "../libft/libft.h"

#define PATH_MAX 4096

static int	add_new_item(t_map *map, size_t index, const char *name, const char *value)
{
	t_item	*new_item;

	new_item = item_new((char *)name, (char *)value);
	if (!new_item)
		return (-1);
	new_item->next = map->table[index];
	map->table[index] = new_item;
	return (0);
}

char	*ft_strtrim_free(char *str, const char *set)
{
	char	*new_str;

	new_str = ft_strtrim(str, set);
	free(str);
	return (new_str);
}

static unsigned int	hash_function(const char *name)
{
	unsigned int	hash;
	const char		*tmp;

	hash = 0;
	tmp = name;
	while (*tmp)
	{
		hash = (hash * 31 + *tmp) % TABLE_SIZE;
		tmp++;
	}
	return (hash);
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

void	map_init(t_map *map)
{
	char	buff[PATH_MAX];
	char	*pwd_var;

	if (getcwd(buff, PATH_MAX) == NULL)
		return ;
	pwd_var = ft_strjoin("PWD=", buff);
	if (!pwd_var)
		return ;
	map_put(map, pwd_var);
	free(pwd_var);
}

t_map	*map_new(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map_init(map);
	return (map);
}

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

int	map_put(t_map *map, const char *string)
{
	char	*equal_pos;
	char	*name;
	char	*value;
	int		result;

	equal_pos = ft_strchr(string, '=');
	if (!equal_pos)
		return (-1);
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
			return (current->value ? 0 : -1);
		}
		current = current->next;
	}
	return (add_new_item(map, index, name, value));
}


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

static void	free_item(t_item *item)
{
	free(item->name);
	free(item->value);
	free(item);
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


// static unsigned int hash_function(const char *name) 
// {
// 	unsigned int hash = 0;
// 	while (*name)
// 	{
// 		hash = (hash * 31 + *name) % TABLE_SIZE;
// 		name++;
// 	}
// 	return hash;
// }

// t_item *item_new(char *name, char *value) 
// {
// 	t_item *item = malloc(sizeof(t_item));
// 	if (!item)
// 		return NULL;
// 	item->name = strdup(name);
// 	item->value = strdup(value);
// 	item->next = NULL;
// 	return item;
// }

// void	map_init(t_map *map)
// {
// 	char buff[PATH_MAX];
// 	getcwd(buff, PATH_MAX);
// 	map_put(map, ft_strjoin("PWD=",buff));
// }

// t_map *map_new(void) 
// {
// 	t_map *map = calloc(1, sizeof(t_map));
// 	map_init(map);
// 	return map;
// }

// char *map_get(t_map *map, const char *name) 
// {
// 	if (!map || !name)
// 		return NULL; size_t index = hash_function(name);
// 	t_item *current = map->table[index];
// 	
// 	while (current) 
// 	{
// 		if (strcmp(current->name, name) == 0)
// 			return current->value;
// 		current = current->next;
// 	}
// 	return NULL;
// }

// int map_put(t_map *map, const char *string) 
// {
// 	char *equal_pos = strchr(string, '=');
// 	if (!equal_pos)
// 		return -1;
// 	
// 	char *name = strndup(string, equal_pos - string);
// 	char *value = strdup(equal_pos + 1);
// 	
// 	int result = map_set(map, name, value);

// 	free(name);
// 	free(value);
// 	return result;
// }

// int map_set(t_map *map, const char *name, const char *value) 
// {
// 	if (!map || !name)
// 		return -1;
// 		
// 	size_t index = hash_function(name);
// 	t_item *current = map->table[index];
// 	
// 	while (current)
// 	{
// 		if (strcmp(current->name, name) == 0) 
// 		{
// 			free(current->value);
// 			current->value = strdup(value);
// 			return 0;
// 		}
// 		current = current->next;
// 	}
// 	
// 	t_item *new_item = item_new((char *)name, (char *)value);
// 	if (!new_item)
// 		return -1;
// 	new_item->next = map->table[index];
// 	map->table[index] = new_item;
// 	return 0;
// }

// int map_unset(t_map *map, const char *name) 
// {
// 	if (!map || !name)
// 		return -1;
// 	unsigned int index = hash_function(name);
// 	t_item *current = map->table[index];
// 	t_item *prev = NULL;

// 	while (current) 
// 	{
// 		if (strcmp(current->name, name) == 0) 
// 		{
// 			if (prev)
// 				prev->next = current->next;
// 			else
// 				map->table[index] = current->next;
// 			free(current->name);
// 			free(current->value);
// 			free(current);
// 			return 0;
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// 	return -1;
// }


