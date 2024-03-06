/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:47:41 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 00:49:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	img_up(t_entity *entity, float dt)
{
	float	y;
	float	diff;

	y = (float)entity->base.y;
	diff = y - entity->movement->tar.y;
	entity->move_step += entity->move_speed * dt;
	if (entity->move_step < 1.0f)
		return ;
	if (fabs(diff) > entity->move_step)
		y -= entity->move_step;
	else
	{
		y = entity->movement->tar.y;
		entity->movement->active = false;
	}
	entity->move_step = 0.0f;
	entity->base.y = (int)roundf(y);
}

void	img_right(t_entity *entity, float dt)
{
	float	x;
	float	diff;

	x = (float)entity->base.x;
	diff = entity->movement->tar.x - x;
	entity->move_step += entity->move_speed * dt;
	if (entity->move_step < 1.0f)
		return ;
	if (fabs(diff) > entity->move_step)
		x += entity->move_step;
	else
	{
		x = entity->movement->tar.x;
		entity->movement->active = false;
	}
	entity->move_step = 0.0f;
	entity->base.x = (int)roundf(x);
}

void	img_down(t_entity *entity, float dt)
{
	float	y;
	float	diff;

	y = (float)entity->base.y;
	diff = entity->movement->tar.y - y;
	entity->move_step += entity->move_speed * dt;
	if (entity->move_step < 1.0f)
		return ;
	if (fabs(diff) > entity->move_step)
		y += entity->move_step;
	else
	{
		y = entity->movement->tar.y;
		entity->movement->active = false;
	}
	entity->move_step = 0.0f;
	entity->base.y = (int)roundf(y);
}

void	img_left(t_entity *entity, float dt)
{
	float	x;
	float	diff;

	x = (float)entity->base.x;
	diff = x - entity->movement->tar.x;
	entity->move_step += entity->move_speed * dt;
	if (entity->move_step < 1.0f)
		return ;
	if (fabs(diff) > entity->move_step)
		x -= entity->move_step;
	else
	{
		x = entity->movement->tar.x;
		entity->movement->active = false;
	}
	entity->move_step = 0.0f;
	entity->base.x = (int)roundf(x);
}

void	move_image(t_entity *entity, float dt)
{
	static t_img_move	move[4] = {img_up, img_right, img_down, img_left};

	move[entity->movement->to](entity, dt);
	sync_anim(entity);
}
