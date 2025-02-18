/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:40 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 12:09:43 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

unsigned int	hash_function(const char *name)
{
	unsigned int	hash;
	const char		*tmp;

	hash = 0;
	tmp = name;
	while (*tmp)
	{
		hash = (hash * 31 + *tmp) % TABLE_SIZE;
		tmp++;
	}
	return (hash);
}

char	*ft_strtrim_free(char *str, const char *set)
{
	char	*new_str;

	new_str = ft_strtrim(str, set);
	free(str);
	return (new_str);
}
