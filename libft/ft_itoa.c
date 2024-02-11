/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:06:58 by aklein            #+#    #+#             */
/*   Updated: 2023/10/28 20:28:27 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	abs_val(int n)
{
	if (n >= 0)
		return (n);
	return (n * -1);
}

static size_t	count_digits(int n)
{
	size_t	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	size_t	i;
	size_t	digits;
	int		is_negative;

	is_negative = 0;
	if (n < 0)
		is_negative = 1;
	digits = count_digits(n) + is_negative;
	nbr = (char *)malloc(digits + 1);
	if (!nbr)
		return (NULL);
	nbr[digits] = '\0';
	i = digits - 1;
	if (n == 0)
		nbr[i] = '0';
	while (n != 0)
	{
		nbr[i--] = '0' + abs_val(n % 10);
		n /= 10;
	}
	if (is_negative)
		nbr[0] = '-';
	return (nbr);
}
