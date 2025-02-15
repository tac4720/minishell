/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:06:43 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/29 18:57:15 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (unsigned char *)dest;
	ptr2 = (const unsigned char *)src;
	if (ptr1 == ptr2)
		return (dest);
	if (ptr1 < ptr2 || ptr1 >= ptr2 + num)
	{
		while (num--)
			*ptr1++ = *ptr2++;
	}
	else
	{
		ptr1 += num;
		ptr2 += num;
		while (num--)
			*(--ptr1) = *(--ptr2);
	}
	return (dest);
}
