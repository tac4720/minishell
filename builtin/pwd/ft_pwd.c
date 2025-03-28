/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:48 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 17:28:44 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../builtin_execute/builtin.h"

void	ft_pwd(char **args, t_context *context)
{
	char	*buff;
	char	*path;

	(void)context;
	buff = malloc(PATH_MAX);
	if (!buff)
	{
		free_and_exit(context, args, 1);
	}
	path = getcwd(buff, PATH_MAX);
	if (path == NULL)
	{
		perror("pwd");
		free(buff);
		free_and_exit (context, args, 1);
	}
	ft_printf("%s\n", path);
	free(buff);
	free_and_exit (context, args, 0);
}
