/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:05:25 by aklein            #+#    #+#             */
/*   Updated: 2023/10/26 17:46:10 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*next_word(char const **str, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i] && (*str)[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (**str && **str != c)
	{
		word[i] = **str;
		(*str)++;
		i++;
	}
	word[i] = '\0';
	while (**str && **str == c)
		(*str)++;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	str_arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str_arr)
		return (NULL);
	i = 0;
	while (i < words)
	{
		str_arr[i] = next_word(&s, c);
		if (!str_arr[i])
		{
			while (--i)
				free(str_arr[i]);
			free(str_arr);
			return (NULL);
		}
		i++;
	}
	str_arr[i] = NULL;
	return (str_arr);
}
