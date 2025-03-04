
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:36 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/02 22:05:28 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../builtin_execute/builtin.h"

static int	count_entries(t_map *environ)
{
	int		i;
	int		count;
	t_item	*current;

	i = 0;
	count = 0;
	while (i < TABLE_SIZE)
	{
		current = environ->table[i];
		while (current)
		{
			count++;
			current = current->next;
		}
		i++;
	}
	return (count);
}

static char	**allocate_list(t_map *environ, int *j)
{
	char	**list;
	int		total;

	total = count_entries(environ);
	list = (char **)malloc(sizeof(char *) * (total + 1));
	*j = 0;
	return (list);
}

static char	**fill_list(t_map *environ, char **list, int *j)
{
	int		i;
	t_item	*current;

	i = 0;
	while (i < TABLE_SIZE)
	{
		current = environ->table[i];
		while (current)
		{
			list[*j] = malloc(ft_strlen(current->name) + 1);
			if (!list[*j])
			{
				while (--(*j) >= 0)
					free(list[*j]);
				free(list);
				return (NULL);
			}
			ft_strlcpy(list[*j], current->name, ft_strlen(current->name) + 1);
			current = current->next;
			(*j)++;
		}
		i++;
	}
	list[*j] = NULL;
	return (list);
}

char	**hashmap_to_list(t_map *environ)
{
	char	**list;
	int		j;

	list = allocate_list(environ, &j);
	if (!list)
		return (NULL);
	return (fill_list(environ, list, &j));
}

void	sort_list(char **list)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	if (!list)
		return ;
	len = 0;
	while (list[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (strcmp(list[j], list[j + 1]) > 0)
			{
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
}

void	print_sorted(t_map *environ)
{
	char	**list;
	char	*value;
	int		i;

	i = 0;
	list = hashmap_to_list(environ);
	if (!list)
		return ;
	sort_list(list);
	while (list[i])
	{
		value = map_get(environ, list[i]);
		if (ft_strncmp(value, "@", 1) != 0)
			ft_printf("%s=%s\n", list[i], value);
		free(list[i]);
		i++;
	}
	free(list);
}

void	ft_env(char **args, t_context *context)
{
	t_map	*env;

	env = context->environ;
	if (args[1] != NULL)
	{
		free_and_exit(context, args, 1);
	}
	print_sorted(env);
	free_and_exit(context, args, 0);
}

void	ft_env_p(char **args, t_context *context)
{
	t_map	*env;

	env = context->environ;
	if (args[1] != NULL)
	{
		free_and_exit(context, args, 1);
	}
	print_sorted(env);
	context->last_status = 0;
}

