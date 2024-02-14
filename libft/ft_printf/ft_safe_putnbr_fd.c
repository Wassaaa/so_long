/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_putnbr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:10:06 by aklein            #+#    #+#             */
/*   Updated: 2023/11/14 20:54:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_safe_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		if (!ft_safe_putchar_fd('-', fd))
			return (0);
		nb *= -1;
	}
	if (nb > 9)
	{
		if (!ft_safe_putnbr_fd(nb / 10, fd))
			return (0);
		if (!ft_safe_putchar_fd(nb % 10 + '0', fd))
			return (0);
	}
	else
		if (!ft_safe_putchar_fd(nb + '0', fd))
			return (0);
	return (1);
}
