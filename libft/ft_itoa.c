/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:42:01 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/28 15:34:12 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n, int count)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		ln *= -1;
	}
	if (ln >= 10)
	{
		count++;
		return (count_digit(ln / 10, count));
	}
	else
	{
		count++;
		return (count);
	}
}

static void	recuresive_int(int num, int d, char *str)
{
	long	lnum;

	lnum = num;
	if (lnum < 0)
	{
		lnum *= -1;
	}
	if (lnum >= 10)
	{
		recuresive_int(lnum / 10, d - 1, str);
	}
	str[d] = (lnum % 10) + '0';
}

char	*ft_itoa(int n)
{
	int		l;
	char	*result;

	l = count_digit(n, 0);
	if (n < 0)
		l++;
	result = malloc(sizeof(char) * l + 1);
	if (result == NULL)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
	}
	recuresive_int(n, l - 1, result);
	result[l] = '\0';
	return (result);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s",ft_itoa(-2147483648));
// 	return (0);
// }