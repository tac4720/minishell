/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:55:53 by tac472            #+#    #+#             */
/*   Updated: 2025/03/07 15:02:39 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (ft_strncmp(list[j], list[j + 1], ft_strlen(list[j]) + 1) > 0)
			{
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
}
