/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:30:24 by thashimo          #+#    #+#             */
/*   Updated: 2023/11/16 13:44:47 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	char	*mem;

	if (!s1)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	mem = (char *)malloc(sizeof(char) * (j - i + 2));
	if (mem == NULL)
		return (NULL);
	ft_strlcpy(mem, &s1[i], j - i + 2);
	return (mem);
}

// #include <stdio.h>
// int main() {
//     char *s1 = "   example string   ";
// 	char *set = " ";
//     char *trimmed_str = ft_strtrim(s1, set);
//     if (trimmed_str != NULL) {
//         printf("Original string: '%s'\n", s1);
//         printf("Trimmed string: '%s'\n", trimmed_str);
//         free(trimmed_str);
//     } else {
//         printf("Memory allocation failed.\n");
//     }
//     return 0;
// };