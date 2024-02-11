/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:01:24 by aklein            #+#    #+#             */
/*   Updated: 2023/10/26 17:47:54 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest_start);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*new_start;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	new_start = new_str;
	ft_strcpy(new_str, s1);
	new_str += ft_strlen(s1);
	ft_strcpy(new_str, s2);
	return (new_start);
}
