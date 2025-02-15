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
		context->last_status = 1;
		exit(1);
	}
	map_set(context->environ, "PWD", cwd);
	context->last_status = 0;
	exit(0);
}

void	error_check(char **args, t_context *context, char *target_dir)
{
	if (args[2] != NULL)
	{
		ft_putstr_fd(" too many arguments", 2);
		context->last_status = 1;
		exit(1);
	}
	if (args[1])
		target_dir = args[1];
	if (target_dir == NULL)
	{
		target_dir = map_get(context->environ, "HOME");
		if (target_dir == NULL)
		{
			context->last_status = 1;
			exit(1);
		}
	}
}

int ft_cd(char **args, t_context *context)
{
	char    *target_dir;
	int     ret;
	
	error_check(args, context, target_dir);
	// if (args[1])
	// 	target_dir = args[1];
	// if (target_dir == NULL)
	// {
	// 	target_dir = map_get(context->environ, "HOME");
	// 	if (target_dir == NULL)
	// 	{
	// 		context->last_status = 1;
	// 		exit(1);
	// 	}
	// }
	// else if (ft_strncmp(target_dir, "-", 1) == 0)
	// {
	// 	target_dir = map_get(context->environ, "OLDPWD");
	// 	if (target_dir == NULL)
	// 	{
	// 		context->last_status = 1;
	// 		exit(1);
	// 	}
	// 	ft_printf("%s\n", target_dir);
	// }
	ret = chdir(target_dir);
	if (ret != 0)
	{
		context->last_status = 1;
		exit (1);
	}
	return (update_pwd_oldpwd(context));
}
