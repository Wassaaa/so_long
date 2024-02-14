/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prf_print_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:27:37 by aklein            #+#    #+#             */
/*   Updated: 2024/02/14 21:33:55 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	count_digits(int n)
{
	size_t	digits;

	digits = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

int	print_d(t_print *print)
{
	int	my_n;
	int	digit_count;

	my_n = va_arg(print->ap, int);
	digit_count = count_digits(my_n);
	if (my_n < 0)
		digit_count++;
	if (!ft_safe_putnbr_fd(my_n, print->fd))
		return (0);
	print->printed += digit_count;
	return (1);
}
