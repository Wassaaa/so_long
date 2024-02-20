/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:14:00 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 22:12:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_list *safe_lstnew(void *content)
{
	t_list *frame;

	frame = ft_lstnew(content);
	if (!frame)
		error();
	return (frame);
}
