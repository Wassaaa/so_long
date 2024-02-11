/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:29:35 by aklein            #+#    #+#             */
/*   Updated: 2023/10/25 15:30:10 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c_str;

	c_str = (unsigned char *)s;
	while (n--)
	{
		if (*c_str == (unsigned char)c)
			return ((void *)c_str);
		c_str++;
	}
	return (NULL);
}
