#include "environ.h"

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
