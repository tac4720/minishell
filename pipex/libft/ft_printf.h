/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:17:48 by thashimo          #+#    #+#             */
/*   Updated: 2024/02/17 23:29:53 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>

int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putptr(void *ptr);
int	ft_putint(int n);
int	ft_putuint(unsigned int n);
int	ft_puthex_complement(int n);
int	ft_putuhex_complement(int n);
int	ft_puthex(long n);
int	ft_putuhex(long n);
int	ft_puthex_uintptr(uintptr_t n);
int	ft_putptr(void *ptr);
int	is_fo(int c);
int	ft_select(char type, va_list args);
int	ft_printf(const char *format, ...);

#endif
