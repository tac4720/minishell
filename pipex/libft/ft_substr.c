/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:39 by thashimo          #+#    #+#             */
/*   Updated: 2023/11/20 15:49:42 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sub_len;
	char	*mem;

	if (!s)
		return (NULL);
	sub_len = ft_strlen(s + start);
	if (sub_len > len)
		sub_len = len;
	mem = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < sub_len && (size_t)start < ft_strlen(s) && s[start + i])
	{
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
