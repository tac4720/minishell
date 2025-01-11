/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:04:36 by thashimo          #+#    #+#             */
/*   Updated: 2024/02/17 23:08:45 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	size_t	l;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	l = ft_strlen(str);
	write(1, str, l);
	return (l);
}

int	ft_putint(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		count += 11;
		return (count);
	}
	if (n < 0)
	{
		ft_putchar('-');
		count++;
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putint(n / 10);
	}
	ft_putchar('0' + (n % 10));
	count++;
	return (count);
}

int	ft_putuint(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putuint(n / 10);
	}
	ft_putchar('0' + (n % 10));
	count++;
	return (count);
}
