/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_putnbr_base_ul_fd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 03:39:12 by aklein            #+#    #+#             */
/*   Updated: 2023/11/14 20:51:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_base(unsigned long nbr, size_t len, char *base, int fd)
{
	if (nbr >= len)
		if (!print_base(nbr / len, len, base, fd))
			return (0);
	if (!ft_safe_putchar_fd(base[nbr % len], fd))
		return (0);
	return (1);
}

int	ft_safe_putnbr_base_ul_fd(unsigned long nbr, char *base, int fd)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (print_base(nbr, base_len, base, fd))
		return (1);
	return (0);
}
