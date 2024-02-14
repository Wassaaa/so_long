/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prf_parse_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:53:12 by aklein            #+#    #+#             */
/*   Updated: 2023/11/07 02:13:39 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_spec(t_print *print)
{
	size_t	i;

	i = 0;
	print->frm++;
	if (ft_strchr(SPECS, print->frm[i]) == 0)
		return (0);
	print->spec_i = i;
	print->spec = print->frm[i];
	return (1);
}
