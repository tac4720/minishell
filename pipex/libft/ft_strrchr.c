/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:50:47 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/29 19:06:46 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	char	*result;

	result = NULL;
	while (*str)
	{
		if (*str == (unsigned char)c)
			result = str;
		str++;
	}
	if (*str == (unsigned char)c)
		result = str;
	return (result);
}
