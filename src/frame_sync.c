/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:46:24 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:11:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	sync_entity(t_anim *current, int x, int y)
{
	t_list		*frames;
	mlx_image_t	*img;

	frames = current->frames;
	while (frames)
	{
		img = (mlx_image_t *)frames->content;
		img->instances[current->instance].x = x;
		img->instances[current->instance].y = y;
		frames = frames->next;
	}
}

void	sync_anim(t_entity *entity)
{
	int	x;
	int	y;

	x = entity->base.x;
	y = entity->base.y;
	sync_entity(entity->current, x, y);
}
