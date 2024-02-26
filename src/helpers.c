/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:14:00 by aklein            #+#    #+#             */
/*   Updated: 2024/02/27 00:04:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	*safe_ft_calloc(size_t count, size_t size)
{
	void	*my_calloc;

	my_calloc = ft_calloc(count, size);
	if (!my_calloc)
		error();
	return (my_calloc);
}

t_list *safe_lstnew(void *content)
{
	t_list *frame;

	frame = ft_lstnew(content);
	if (!frame)
		error();
	return (frame);
}
