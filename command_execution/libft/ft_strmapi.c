/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:53:17 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/29 18:19:35 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_array;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	new_array = ft_strdup(s);
	if (new_array == NULL)
		return (NULL);
	while (new_array[i])
	{
		new_array[i] = (*f)(i, new_array[i]);
		i++;
	}
	return (new_array);
}

// int main()
// {
// 	char const *s = "Hello, World!";
// 	char *result;

// 	result = ft_strmapi(s, change_to_upper);
// 	printf("%s\n", result);

// 	return 0;
// }
