#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../builtin_execute/builtin.h"

int	ft_pwd(char **args, t_context *context)
{
	char	*buff;
	char	*path;

	(void)context;
	// if (args[1] != NULL)
	// {
	// 	fprintf(stderr, "pwd: too many arguments\n");
	// 	return (1);
	// }
	buff = malloc(PATH_MAX);
	if (!buff)
	{
		return (1);
	}
	path = getcwd(buff, PATH_MAX);
	if (path == NULL)
	{
		perror("pwd");
		free(buff);
		return (1);
	}
	printf("%s\n", path);
	free(buff);
	return (0);
}
