/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:11:59 by asebban           #+#    #+#             */
/*   Updated: 2024/11/28 10:03:31 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(int c);
int	ft_putstr(const char *str);
int	ft_putnbr(int n);
int	print_hex(unsigned long num);
int	ft_put_uns_nbr(unsigned int n);
int	print_low_hex(unsigned int num);
int	print_up_hex(unsigned int num);

#endif