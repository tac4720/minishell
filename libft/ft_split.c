/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:24:29 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/29 19:17:26 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **list, int count)
{
	while (count >= 0)
	{
		free(list[count]);
		count--;
	}
	free(list);
}

static char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*mem;

	i = 0;
	mem = malloc(sizeof(char) * n + 1);
	if (mem == NULL)
		return (NULL);
	while (i < n && str[i])
	{
		mem[i] = str[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

static char	**ft_divide(char **list, const char *str, int c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		if (((i == 0 || str[i - 1] == c)) && (str[i] != c))
		{
			while (str[i + j] != c && str[i + j] != '\0')
				j++;
			list[k] = ft_strndup(&str[i], j);
			if (!list[k])
			{
				ft_free(list, k - 1);
				return (NULL);
			}
			k++;
		}
		i++;
	}
	list[k] = NULL;
	return (list);
}

static int	count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	if (!str)
		return (0);
	i = 1;
	count = 0;
	while (str[i])
	{
		if ((((str[i - 1] == sep) && str[i] != sep)
				|| (i == 1 && str[i - 1] != sep)))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	**ft_split(const char *str, char c)
{
	char	**list;

	if (!str)
		return (NULL);
	list = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!list)
		return (NULL);
	return (ft_divide(list, str, c));
}

// int main(void)
// {
// 	char strs[] = "      split       this for   me  !       ";
// 	char **results = ft_split(strs, ' ');
// 	for (int i = 0; i <6; i++)
// 	{
// 	printf("%s", results[i]);
// 	printf("\n");
// 	}
// 	return (0);
// }