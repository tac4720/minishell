/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:36 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 12:09:43 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../builtin_execute/builtin.h"

void ft_env(char **args, t_context *context)
{
	t_map	*env;
	int 	i;
	t_item	*current;

	env = context->environ;
	i = 0;
	if (args[2] != NULL) 
  	{
		free_and_exit (context, args, 1);
  	}

	while (i < TABLE_SIZE)
    {
      current = env->table[i];
      while (current)
      {
        ft_printf("%s=%s\n", current->name, current->value);
        current = current->next;
      }
		i++;
    }
	free_and_exit (context, args, 0);
}
