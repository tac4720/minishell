/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:02:51 by thashimo          #+#    #+#             */
/*   Updated: 2024/02/17 23:47:17 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

int	ft_putptr(void *ptr)
{
	int	count;

	count = 0;
	ft_putstr("0x");
	count += 2;
	count += ft_puthex_uintptr((uintptr_t)ptr);
	return (count);
}

int	is_fo(int c)
{
	size_t				i;
	const unsigned char	f_list[] = "cspdiuxX%%";

	i = 0;
	while (f_list[i])
	{
		if ((unsigned char)c == f_list[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_select(char type, va_list args)
{
	if (type == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (type == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (type == 'd' || type == 'i')
		return (ft_putint(va_arg(args, int)));
	if (type == 'u')
		return (ft_putuint(va_arg(args, unsigned int)));
	if (type == 'x')
		return (ft_puthex_complement(va_arg(args, long)));
	if (type == 'X')
		return (ft_putuhex_complement(va_arg(args, long)));
	if (type == '%')
		return (ft_putchar('%'));
	return (0);
}

void	ft_printf_helper(const char *format, va_list *args, int *ret)
{
	size_t	i;
	int		f;

	i = 0;
	f = 0;
	while (format[i])
	{
		if (is_fo(format[i]) && f)
		{
			*ret += ft_select(format[i], *args);
			f = 0;
		}
		else if (format[i] == '%')
		{
			f = 1;
		}
		else
		{
			ft_putchar(format[i]);
			(*ret)++;
		}
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	ret = 0;
	va_start(args, format);
	ft_printf_helper(format, &args, &ret);
	va_end(args);
	return (ret);
}

//#include <stdio.h>
//int main()
//{
//	int hex;
//	int	ret;

//	ret = 0;
//	hex = 1024;

//	ret = ft_printf("%s\n", "hello");
//	printf("%i\n", ret);

//	ret = printf("%s\n", "hello");
//	printf("%i\n", ret);	
//}
