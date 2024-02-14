/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prf_print_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 02:16:47 by aklein            #+#    #+#             */
/*   Updated: 2023/11/14 20:16:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_s(t_print *print)
{
	char	*my_str;

	my_str = va_arg(print->ap, char *);
	if (!my_str)
	{
		if (!ft_safe_putstr_fd("(null)", print->fd))
			return (0);
		print->printed += 6;
		return (1);
	}
	if (!ft_safe_putstr_fd(my_str, print->fd))
		return (0);
	print->printed += ft_strlen(my_str);
	return (1);
}
