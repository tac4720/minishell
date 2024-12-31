/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:04:42 by thashimo          #+#    #+#             */
/*   Updated: 2024/02/17 23:19:43 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_complement(int n)
{
	int				ret;
	unsigned int	abs_val;
	unsigned int	complement;

	ret = 0;
	if (n < 0)
	{
		abs_val = (unsigned int)(-n);
		complement = ~abs_val + 1;
		return (ft_puthex(complement));
	}
	else
	{
		return (ft_puthex(n));
	}
	return (ret);
}

int	ft_putuhex_complement(int n)
{
	int				ret;
	unsigned int	abs_val;
	unsigned int	complement;

	ret = 0;
	if (n < 0)
	{
		abs_val = (unsigned int)(-n);
		complement = ~abs_val + 1;
		return (ft_putuhex(complement));
	}
	else
	{
		return (ft_putuhex(n));
	}
	return (ret);
}

int	ft_puthex(long n)
{
	const char	map[] = "0123456789abcdef";
	int			count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthex(n / 16);
	}
	ft_putchar(map[n % 16]);
	count++;
	return (count);
}

int	ft_putuhex(long n)
{
	const char	map[] = "0123456789ABCDEF";
	int			count;

	count = 0;
	if (n >= 16)
	{
		count += ft_putuhex(n / 16);
	}
	ft_putchar(map[n % 16]);
	count++;
	return (count);
}

int	ft_puthex_uintptr(uintptr_t n)
{
	const char	map[] = "0123456789abcdef";
	int			count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthex_uintptr(n / 16);
	}
	ft_putchar(map[n % 16]);
	count++;
	return (count);
}
