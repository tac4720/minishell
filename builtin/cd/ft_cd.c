#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../builtin_execute/builtin.h"

static int  update_pwd(t_context *context)
{
	char    *oldpwd;
	char    cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		context->last_status = 1; exit(1);
	}
	map_set(context->environ, "PWD", cwd);
	context->last_status = 0;
	exit(0);
}

void	error_check(char **args, t_context *context)
{
	if (args[2] != NULL)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		context->last_status = 1;
		exit(1);
	}
}

void ft_cd(char **args, t_context *context)
{
	char    *target_dir;
	int     ret;
	
	error_check(args, context);
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
	// if (target_dir == NULL)
	// {
	// 	target_dir = map_get(context->environ, "HOME");
	// 	if (target_dir == NULL)
	// 	{
	// 		context->last_status = 1;
	// 		exit(1);
	// 	}
	// }
	ret = chdir(target_dir);
	// printf("ret:%i\n", ret);
	if (ret != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		context->last_status = 1;
		exit (1);
	}
	update_pwd(context);
	exit(0);
}
