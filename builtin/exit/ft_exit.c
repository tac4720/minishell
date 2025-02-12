#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "../builtin_execute/builtin.h"

/*
POSIX準拠の終了コード

数値エラー: 255

引数過多: 1

正常終了: 指定数値 (0-255)
*/

static bool	is_numeric(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (false);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		str++;
	}
	return (true);
}

int	ft_exit(char **args, t_context *context)
{
	long	status;
	char	*endptr;

	if (args[1] == NULL)
		exit(context->last_status % 256);
	if (args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		context->last_status = 1;
		return (1);
	}
	if (!is_numeric(args[1]))
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	errno = 0;
	status = strtol(args[1], &endptr, 10);
	if (errno == ERANGE || *endptr != '\0')
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	exit((unsigned char)status);
}
