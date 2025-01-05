#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "environ.h"


static unsigned int hash_function(const char *name) 
{
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31 + *name) % TABLE_SIZE;
        name++;
    }
    return hash;
}

t_item *item_new(char *name, char *value) 
{
    t_item *item = malloc(sizeof(t_item));
    if (!item)
        return NULL;
    item->name = strdup(name);
    item->value = strdup(value);
    item->next = NULL;
    return item;
}

t_map *map_new(void) 
{
    t_map *map = calloc(1, sizeof(t_map));
    return map;
}

char *map_get(t_map *map, const char *name) 
{
    if (!map || !name)
        return NULL;
    size_t index = hash_function(name);
    t_item *current = map->table[index];
    
    while (current) 
    {
        if (strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

int map_put(t_map *map, const char *string) 
{
    char *equal_pos = strchr(string, '=');
    if (!equal_pos)
        return -1;
    
    char *name = strndup(string, equal_pos - string);
    char *value = strdup(equal_pos + 1);
    
    int result = map_set(map, name, value);
    
    free(name);
    free(value);
    return result;
}

int map_set(t_map *map, const char *name, const char *value) 
{
    if (!map || !name)
        return -1;
        
    size_t index = hash_function(name);
    t_item *current = map->table[index];
    
    while (current)
    {
        if (strcmp(current->name, name) == 0) 
        {
            free(current->value);
            current->value = strdup(value);
            return 0;
        }
        current = current->next;
    }
    
    t_item *new_item = item_new((char *)name, (char *)value);
    if (!new_item)
        return -1;
    new_item->next = map->table[index];
    map->table[index] = new_item;
    return 0;
}

int map_unset(t_map *map, const char *name) 
{
    if (!map || !name)
        return -1;
        
    unsigned int index = hash_function(name);
    t_item *current = map->table[index];
    t_item *prev = NULL;
    
    while (current) 
    {
        if (strcmp(current->name, name) == 0) 
        {
            if (prev)
                prev->next = current->next;
            else
                map->table[index] = current->next;
            
            free(current->name);
            free(current->value);
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}
