#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include "../builtin_execute/builtin.h"


static int    write_str(const char *str)
{
    if (write(STDOUT_FILENO, str, ft_strlen(str)) == -1)
    {
        perror("echo: write error");
        return (1);
    }
    return (0);
}

static int    write_newline(void)
{
    if (write(STDOUT_FILENO, "\n", 1) == -1)
    {
        perror("echo: write error");
        return (1);
    }
    return (0);
}

void    ft_echo(char **args, t_context *context)
{
    size_t    i;
    int        flag;

    (void)context;
    i = 1;
    flag = 0;
    if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
    {
        flag = 1;
        i++;
    }
    while (args[i])
    {
        ft_printf(args[i]);
        if (args[i + 1])
            ft_printf(" ");
        i++;
    }
    if (flag == 0)
        ft_printf("\n");
    free_and_exit(context, args, 0);
}

