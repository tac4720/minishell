#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../builtin_execute/builtin.h"

static int  update_pwd_oldpwd(t_context *context)
{
	char    *oldpwd;
	char    cwd[PATH_MAX];

	oldpwd = map_get(context->environ, "PWD");
	if (oldpwd)
		map_set(context->environ, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (1);
	}
	map_set(context->environ, "PWD", cwd);
	return (0);
}

int ft_cd(char **args, t_context *context)
{
	char    *target_dir;
	int     ret;

	if (args[1])
	target_dir = args[1];
	if (target_dir == NULL)
	{
		target_dir = map_get(context->environ, "HOME");
		if (target_dir == NULL)
		{
			context->last_status = 1;
			exit(1);
			return (1);
		}
	}
	else if (strcmp(target_dir, "-") == 0)
	{
		target_dir = map_get(context->environ, "OLDPWD");
		if (target_dir == NULL)
		{
			context->last_status = 1;
			exit(1);
		}
		printf("%s\n", target_dir);
	}
	ret = chdir(target_dir);
	if (ret != 0)
	{
		perror("chdir");
		context->last_status = 1;
		exit (1);
	}
	return (update_pwd_oldpwd(context));
}
