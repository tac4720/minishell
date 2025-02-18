/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:41 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 12:09:43 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void    print_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
}

void    ft_exit(char **args, t_context *context)
{
    int	status;
    int        error_flag;

    error_flag = 0;
    if (!args[1])
        free_and_exit(context, args, 1);
    if (args[2])
    {
        print_error(" too many arguments");
        context->last_status = 1;
        free_and_exit(context, args, 1);
    }
    status = ft_atoi(args[1]);
    if (error_flag || !is_numeric(args[1]))
    {
        print_error(" numeric argument required");
        context->last_status = 2;
        free_and_exit(context, args, 2);
    }
    free_and_exit(context, args, status);
}

