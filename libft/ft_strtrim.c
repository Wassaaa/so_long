/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:02:05 by aklein            #+#    #+#             */
/*   Updated: 2023/10/26 17:46:55 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_size(char const *s, char const *set)
{
	size_t	counter;

	counter = 0;
	while (*s && ft_strchr(set, *s))
		s++;
	while (*s)
	{
		counter++;
		s++;
	}
	while (counter > 0 && *--s && ft_strchr(set, *s))
		counter--;
	return (counter);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	char	*start_str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	len = count_size(s1, set);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	start_str = new_str;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (len--)
		*(new_str++) = *(s1++);
	*new_str = '\0';
	return (start_str);
}
