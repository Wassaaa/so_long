/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:11:38 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 00:22:10 by aklein           ###   ########.fr       */
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

void	ent_up(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y - 1) * game->map->width) + entity->pos.x;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	entity->movement->anim = entity->anims[A_UP];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_L];
			add_move(game);
		}
		move_it(game, entity, UP);
		entity->pos.y--;
	}
	else
	{
		entity->movement->active = false;
	}
	entity->next = entity->movement->anim;
}

void	ent_right(t_game *game, t_entity *entity)
{
	int	dest;

	dest = (entity->pos.y * game->map->width) + entity->pos.x + 1;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_RIGHT];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_R];
			add_move(game);
		}
		move_it(game, entity, RIGHT);
		entity->pos.x++;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
}

void	ent_down(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y + 1) * game->map->width) + entity->pos.x;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	entity->movement->anim = entity->anims[A_DOWN];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_R];
			add_move(game);
		}
		move_it(game, entity, DOWN);
		entity->pos.y++;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
}

void	ent_left(t_game *game, t_entity *entity)
{
	int	dest;

	dest = (entity->pos.y * game->map->width) + entity->pos.x - 1;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	entity->movement->anim = entity->anims[A_LEFT];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_L];
			add_move(game);
		}
		move_it(game, entity, LEFT);
		entity->pos.x--;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
}

void	move_it(t_game *game, t_entity *entity, int to)
{
	t_point	tar;

	entity->movement->active = true;
	tar.x = (entity->facing->x * game->tile_size) + entity->off.x;
	tar.y = (entity->facing->y * game->tile_size) + entity->off.y;
	entity->movement->tar = tar;
	entity->movement->to = to;
}