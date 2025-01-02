typedef struct s_map		t_map;
typedef struct s_item		t_item;

struct s_item {
	char	*name;
	char	*value;
	t_item	*next;
};

struct s_map {
	t_item	item_head;
};

t_item	*item_new(char *name, char *value);
t_map		*map_new(void);
char		*map_get(t_map *map, const char *name);
int			map_put(t_map *map, const char *string);
int			map_set(t_map *map, const char *name, const char *value);
int			map_unset(t_map *map, const char *name);
