/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:35:45 by thashimo          #+#    #+#             */
/*   Updated: 2023/11/16 13:14:30 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if ((c == ' ' || c == '\n' || c == '\t' || c == '\v'
			|| c == '\r' || c == '\f'))
		return (1);
	return (0);
}

static int	ft_isnum(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	check(long sign, long digit, long result)
{
	if (sign == 1)
	{
		if (result > (LONG_MAX - digit) / 10)
		{
			return (1);
		}
	}
	else
	{
		if (result < (LONG_MIN + digit) / 10)
		{
			return (-1);
		}
	}
	return (0);
}

int	skip(const char *nptr, long *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = *sign * -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	length;
	long	result;
	long	sign;

	length = ft_strlen(nptr);
	result = 0;
	sign = 1;
	i = skip(nptr, &sign);
	while (i < length && ft_isnum(nptr[i]))
	{
		if (check(sign, nptr[i] - '0', result) == 1)
			return ((int)(LONG_MAX));
		if (check(sign, nptr[i] - '0', result) == -1)
			return ((int)(LONG_MIN));
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

//#include <string.h>
//#include <stdio.h>
//int main(void)
//{
//	printf("%i\n",ft_atoi("-3485703475984375083475"));
//	printf("%i\n",atoi("-3485703475984375083475"));
//	printf("%i\n",atoi("-32324534444444445444"));
//}