/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:33 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/02 18:34:51 by thashimo         ###   ########.fr       */
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
	int			i;
	int			j;
	int			flag;

	i = 1;
	flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break;
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
