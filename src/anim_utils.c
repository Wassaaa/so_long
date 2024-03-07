/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:13:23 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:00:40 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	anim_off(t_anim *anim)
{
	mlx_image_t	*frame;
	t_list		*frames;

	frames = anim->frames;
	while (frames)
	{
		frame = (mlx_image_t *)frames->content;
		frame->instances[anim->instance].enabled = false;
		frames = frames->next;
	}
	anim->is_active = false;
}

void	movement_animation(t_entity *entity)
{
	if (entity->current && entity->current->full_cycle)
	{
		if (entity->current->cur_f != 0)
			entity->next = NULL;
		else
		{
			anim_off(entity->current);
			entity->current = entity->next;
		}
	}
	else if (entity->next != entity->current)
	{
		if (entity->current)
			anim_off(entity->current);
		entity->current = entity->next;
	}
	sync_anim(entity);
	entity->next = NULL;
	entity->current->is_active = true;
}
