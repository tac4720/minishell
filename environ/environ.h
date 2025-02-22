/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:12 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 20:55:30 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_map		t_map;
typedef struct s_item		t_item;

# define TABLE_SIZE 1021

typedef struct s_item
{
	char			*name;
	char			*value;
	struct s_item	*next;
}	t_item;

typedef struct s_map
{
	t_item	*table[TABLE_SIZE];
}	t_map;

t_item			*item_new(char *name, char *value);
void			free_item(t_item *item);
t_map			*map_new(void);
void			map_init(t_map *map);
char			*map_get(t_map *map, const char *name);
int				map_put(t_map *map, const char *string);
int				map_set(t_map *map, const char *name, const char *value);
int				map_unset(t_map *map, const char *name);
int				add_new_item(t_map *map, size_t index, const char *name,
					const char *value);
unsigned int	hash_function(const char *name);
char			*ft_strtrim_free(char *str, const char *set);
#endif
