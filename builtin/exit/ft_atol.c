/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:39:02 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/02 18:58:56 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_execute/builtin.h"

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

static int	check(long sign, long digit, long long result)
{
	if (sign == 1)
	{
		if (result > (LLONG_MAX - digit) / 10)
		{
			return (1);
		}
	}
	else
	{
		if (result < (LLONG_MIN + digit) / 10)
		{
			return (-1);
		}
	}
	return (0);
}

int	skip(const char *nptr, int *sign)
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

long long	ft_atol(const char *nptr)
{
	size_t		i;
	size_t		length;
	long long	result;
	int			sign;

	length = ft_strlen(nptr);
	result = 0;
	sign = 1;
	i = skip(nptr, &sign);
	while (i < length && ft_isnum(nptr[i]))
	{
		if (check(sign, nptr[i] - '0', result) == 1)
			return ((int)(LLONG_MAX));
		if (check(sign, nptr[i] - '0', result) == -1)
			return ((int)(LLONG_MIN));
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}
