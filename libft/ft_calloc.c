/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:51:22 by aklein            #+#    #+#             */
/*   Updated: 2023/10/28 16:21:53 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*my_calloc;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	if (count && size > SIZE_MAX / count)
		return (NULL);
	my_calloc = (char *)malloc(count * size);
	if (!my_calloc)
		return (NULL);
	ft_bzero(my_calloc, count * size);
	return ((void *)my_calloc);
}
