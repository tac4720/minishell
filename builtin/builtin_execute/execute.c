#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include <stdio.h>
int	is_builtin(char *str)
{
	int i = 0;
	char *builtin_cmds[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	while (builtin_cmds[i] != NULL)
	{
		if (strcmp(str, builtin_cmds[i]) == 0)
		{
			return i;	
		}
		i++;
	}
	return (-1);
}

int builtin_execute(char *line)
{
	char *args[] = {line, NULL, NULL};
	int select = is_builtin(line);
	if (select == 0)
	{
		ft_cd(args);
		return (1);
	}
	else if (select == 1)
	{
		ft_echo(args);
		return (1);
	}
	else if (select == 2)
	{
		ft_env(args);
		return (1);
	}
	else if (select == 3)
	{
		ft_exit(args);
		return (1);
	}
	else if (select == 4)
	{
		ft_export(args);
		return (1);
	}
	else if (select == 5)
	{
		ft_pwd(args);
		return (1);
	}
	else if (select == 6)
	{
		ft_unset(args);
	}
	return (0);
}
