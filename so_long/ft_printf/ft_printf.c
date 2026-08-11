/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:08:51 by asebban           #+#    #+#             */
/*   Updated: 2024/11/28 10:14:10 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(va_list arg, char specifier)
{
	int	print;

	print = 0;
	if (specifier == 'c')
		print += ft_putchar(va_arg(arg, int));
	else if (specifier == 's')
		print += ft_putstr(va_arg(arg, char *));
	else if (specifier == 'p')
		print += print_hex((unsigned long)va_arg(arg, void *));
	else if (specifier == 'd' || specifier == 'i')
		print += ft_putnbr(va_arg(arg, int));
	else if (specifier == 'u')
		print += ft_put_uns_nbr(va_arg(arg, unsigned int));
	else if (specifier == 'x')
		print += print_low_hex(va_arg(arg, unsigned int));
	else if (specifier == 'X')
		print += print_up_hex(va_arg(arg, unsigned int));
	else if (specifier == '%')
		print += write(1, "%", 1);
	else
		print += write(1, &specifier, 1);
	return (print);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		print;

	i = 0;
	print = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!format[i + 1])
				break ;
			print += handle_format(arg, format[i + 1]);
			i++;
		}
		else
			print += ft_putchar(format[i]);
		i++;
	}
	va_end(arg);
	return (print);
}
