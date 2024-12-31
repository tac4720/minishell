/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:41:34 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/28 15:36:43 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;
	int		output;

	ln = n;
	if (ln == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln *= -1;
	}
	if (ln >= 10)
	{
		ft_putnbr_fd(ln / 10, fd);
	}
	output = (ln % 10) + '0';
	write(fd, &(output), 1);
}

// int	main(void)
// {
// 	ft_putnbr_fd(-2147483648,1);
// 	return (0);
// }
