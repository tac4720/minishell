/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:30:18 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/28 15:37:23 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (i < n && haystack[i])
	{
		j = 0;
		while (i + j < n && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)&(haystack[i]));
			j++;
		}
		i++;
	}
	return ((NULL));
}
