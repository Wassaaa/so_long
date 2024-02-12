/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:57:25 by aklein            #+#    #+#             */
/*   Updated: 2023/11/03 19:17:45 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

size_t	count_digits(int n)
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

size_t	count_digits_ui(unsigned int n)
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

size_t	count_digits_hex(unsigned long nb)
{
	size_t	digits;

	digits = 1;
	nb /= 16;
	while (nb != 0)
	{
		digits++;
		nb /= 16;
	}
	return (digits);
}
