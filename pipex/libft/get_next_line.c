/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:32:00 by thashimo          #+#    #+#             */
/*   Updated: 2024/02/24 01:24:24 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft.h"

static char	*read_buff(int *ret, char *buff, char *str)
{
	int	i;
	int	l_nl;

	i = 0;
	l_nl = 0;
	while (buff[i] && 0 < *ret)
	{
		if (buff[i] == '\n')
		{
			str = ft_strnjoin(str, buff, i + 1);
			*ret = *ret - (i + 1);
			l_nl = ft_strlen(buff + i + 1);
			ft_memmove(buff, buff + i + 1, l_nl);
			ft_bzero(buff + l_nl, ft_strlen(buff + l_nl));
			return (str);
		}
		i++;
	}
	return (NULL);
}

static char	*read_line(int fd, int *ret, char *buff, char *str)
{
	*ret = read(fd, buff, BUFFER_SIZE);
	if (*ret == 0)
	{
		free(str);
		return (NULL);
	}
	while (0 < *ret)
	{
		if (ft_strchr(buff, '\n'))
		{
			return (read_buff(ret, buff, str));
		}
		else
		{
			buff[*ret] = '\0';
			str = ft_strnjoin(str, buff, ft_strlen(buff));
			*ret = read(fd, buff, BUFFER_SIZE);
		}
	}
	if (*ret == -1)
		return (free(str), NULL);
	if (!ft_strchr(buff, '\n'))
		ft_bzero(buff, ft_strlen(buff));
	return (str);
}

static char	*read_nextline(int fd, int *ret, char *buff, char *str)
{
	if (*ret == 0)
	{
		free(str);
		return (NULL);
	}
	while (0 < *ret)
	{
		if (ft_strchr(buff, '\n'))
		{
			return (read_buff(ret, buff, str));
		}
		else
		{	
			buff[*ret] = '\0';
			str = ft_strnjoin(str, buff, ft_strlen(buff));
			*ret = read(fd, buff, BUFFER_SIZE);
		}
	}
	if (*ret == -1)
		return (free(str), NULL);
	if (!ft_strchr(buff, '\n'))
		ft_bzero(buff, ft_strlen(buff));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1UL];
	char		*str;
	static int	ret;

	if (fd < 0 || read(fd, buff, 0) == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc(1);
	if (!str)
		return (NULL);
	ft_bzero(str, 1);
	if (*buff)
		return (read_nextline(fd, &ret, buff, str));
	return (read_line(fd, &ret, buff, str));
}
