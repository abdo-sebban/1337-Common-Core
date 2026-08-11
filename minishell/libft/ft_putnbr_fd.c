/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:48:22 by selbouka          #+#    #+#             */
/*   Updated: 2024/11/10 19:12:41 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb1;

	if (fd < 0)
		return ;
	nb1 = n;
	if (nb1 < 0)
	{
		write(fd, "-", 1);
		nb1 *= -1;
	}
	if (nb1 < 10)
	{
		nb1 += 48;
		write (fd, &nb1, 1);
	}
	else
	{
		ft_putnbr_fd(nb1 / 10, fd);
		ft_putnbr_fd(nb1 % 10, fd);
	}
}
