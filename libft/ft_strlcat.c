/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:21:22 by aklein            #+#    #+#             */
/*   Updated: 2023/10/25 18:54:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	offset;
	size_t	s_index;

	if (!dst && dstsize == 0)
		d_len = 0;
	else
		d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	offset = d_len;
	s_index = 0;
	if (dstsize <= d_len)
		return (dstsize + s_len);
	while (*(src + s_index) && s_index < dstsize - d_len - 1)
		*(dst + offset++) = *(src + s_index++);
	*(dst + offset) = '\0';
	return (d_len + s_len);
}
