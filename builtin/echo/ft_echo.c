#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include "../builtin_execute/builtin.h"

int ft_echo(char **args, t_context *context)
{
    size_t i = 1;
    bool flag = false;

    (void)context; 
    if (args[i] && strcmp(args[i], "-n") == 0)
    {
        flag = true;
        i++;
    }

    while (args[i] != NULL)
    {
        if (write(STDOUT_FILENO, args[i], strlen(args[i])) == -1)
        {
            perror("echo: write error");
            return 1;
        }

        if (args[i + 1] != NULL)
        {
            if (write(STDOUT_FILENO, " ", 1) == -1)
            {
                perror("echo: write error");
                return 1;
            }
        }

        i++;
    }
    if (!flag)
    {
        if (write(STDOUT_FILENO, "\n", 1) == -1)
        {
            perror("echo: write error");
            return 1;
        }
    }

    return 0;
}
