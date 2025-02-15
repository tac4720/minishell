#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "../builtin_execute/builtin.h"

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

static void    print_error(const char *msg, int newline)
{
    ft_putstr_fd("exit\n", STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
    if (newline)
        ft_putstr_fd("\n", STDERR_FILENO);
}

static long    safe_strtol(const char *str, int *error)
{
    char    *endptr;
    long    val;

    errno = 0;
    val = strtol(str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0')
    {
        *error = 1;
        return (255);
    }
    return (val);
}

int    ft_exit(char **args, t_context *context)
{
    long    status;
    int        error_flag;

    error_flag = 0;
    if (!args[1])
        exit(context->last_status % 256);
    if (args[2])
    {
        print_error("exit: too many arguments", 1);
        context->last_status = 1;
        return (1);
    }
    status = safe_strtol(args[1], &error_flag);
    if (error_flag || !is_numeric(args[1]))
    {
        print_error("exit: numeric argument required", 1);
        exit(255);
    }
    exit((unsigned char)status);
}

// int	ft_exit(char **args, t_context *context)
// {
// 	long	status;
// 	char	*endptr;

// 	if (args[1] == NULL)
// 		exit(context->last_status % 256);
// 	if (args[2] != NULL)
// 	{
// 		ft_putstr_fd(" too many arguments\n", 2);
// 		context->last_status = 1;
// 		exit(1);
// 	}
// 	if (!is_numeric(args[1]))
// 	{
// 		ft_putstr_fd(" numeric argument required\n", 2);
// 		context->last_status = 2;
// 		exit(2);
// 	}
// 	errno = 0;
// 	status = strtol(args[1], &endptr, 10);
// 	if (errno == ERANGE || *endptr != '\0')
// 	{
// 		ft_putstr_fd(" numeric argument required\n", 2);
// 		exit(255);
// 	}
// 	exit((unsigned char)status);
// }
