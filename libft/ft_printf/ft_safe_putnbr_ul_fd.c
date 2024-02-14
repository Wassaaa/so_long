/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnr_ul_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 03:32:23 by aklein            #+#    #+#             */
/*   Updated: 2023/11/01 20:52:56 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_safe_putnbr_ul_fd(unsigned long n, int fd)
{
	if (n > 9)
	{
		if (!ft_safe_putnbr_ul_fd(n / 10, fd))
			return (0);
		if (!ft_safe_putchar_fd(n % 10 + '0', fd))
			return (0);
	}
	else
	{
		if (!ft_safe_putchar_fd(n + '0', fd))
			return (0);
	}
	return (1);
}
