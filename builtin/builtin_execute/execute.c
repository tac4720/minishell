#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include <stdio.h>

int is_builtin(char *str)
{
    int         i;
    char        *builtin_cmds[8];
    size_t      cmd_len;

    i = 0;
    builtin_cmds[0] = "cd";
    builtin_cmds[1] = "echo";
    builtin_cmds[2] = "env";
    builtin_cmds[3] = "exit";
    builtin_cmds[4] = "export";
    builtin_cmds[5] = "pwd";
    builtin_cmds[6] = "unset";
    builtin_cmds[7] = NULL;
    while (builtin_cmds[i])
    {
        cmd_len = ft_strlen(builtin_cmds[i]);
        if (ft_strncmp(str, builtin_cmds[i], cmd_len + 1) == 0)
            return (i);
        i++;
    }
    return (-1);
}

// int	is_builtin(char *str)
// {
// 	int i = 0;
// 	char *builtin_cmds[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
// 	while (builtin_cmds[i] != NULL)
// 	{
// 		if (strcmp(str, builtin_cmds[i]) == 0)
// 		{
// 			return i;	
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

int builtin_execute(char **args, t_context *context)
{
	// char *args[] = {line, NULL, NULL};
	int select = is_builtin(args[0]);
	if (select == 0)
	{
		ft_cd(args, context);
		return (1);
	}
	else if (select == 1)
	{
		ft_echo(args, context);
		return (1);
	}
	else if (select == 2)
	{
		ft_env(args, context);
		return (1);
	}
	else if (select == 3)
	{
		ft_exit(args, context);
		return (1);
	}
	else if (select == 4)
	{
		ft_export(args, context);
		return (1);
	}
	else if (select == 5)
	{
		ft_pwd(args, context);
		return (1);
	}
	else if (select == 6)
	{
		ft_unset(args, context);
		return (1);
	}
	return (0);
}
