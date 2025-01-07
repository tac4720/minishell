#include "minishell.h"

void free_2d_array(char **array) {
    if (!array) {
        return; // NULLポインタが渡された場合は何もしない
    }

    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]); // 各行を解放
    }

    free(array); // 配列自体を解放
}

char	*make_path(const char *filename)
{
	char    *path_var_content;
    char    **path_dirs;
    int     i;
    char    *tmp;
    char    *full_path;



    path_dirs = NULL;
    path_var_content = getenv("PATH");
    path_dirs = ft_split(path_var_content, ':');
    i = 0;
    while (path_dirs[i])
    {
        full_path = ft_strjoin(path_dirs[i], "/");
        if (full_path == NULL)
            return (NULL);
        tmp = full_path;
        full_path = ft_strjoin(full_path, filename);
        if (full_path == NULL)
            return (NULL);
        free(tmp);
        if (access(full_path, F_OK) == 0)
        {
            free_2d_array(path_dirs);
            return (full_path);
        }
        i++;
    }
    path_var_content = getenv("PATH");
	return (NULL);
}