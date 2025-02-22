/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:33 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 21:17:46 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include "../builtin_execute/builtin.h"

void	ft_echo(char **args, t_context *context)
{
	size_t		i;
	int			flag;

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
