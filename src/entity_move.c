/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:11:38 by aklein            #+#    #+#             */
/*   Updated: 2024/02/24 04:45:55 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	img_up(t_entity *entity)
{
	float	y;
	float	diff;

	y = (float)entity->base.y;
	diff = y - entity->movement->tar.y;
	if (diff > entity->move_speed)
		y -= entity->move_speed;
	else
	{
		y -= diff;
		entity->movement->active = false;
	}
	entity->base.y = (int)roundf(y);
}

void	img_right(t_entity *entity)
{
	float	x;
	float	diff;

	x = (float)entity->base.x;
	diff = entity->movement->tar.x - x;
	if (diff > entity->move_speed)
		x += entity->move_speed;
	else
	{
		x += diff;
		entity->movement->active = false;
	}
	entity->base.x = (int)roundf(x);
}

void	img_down(t_entity *entity)
{
	float	y;
	float	diff;

	y = (float)entity->base.y;
	diff = entity->movement->tar.y - y;
	if (diff > entity->move_speed)
		y += entity->move_speed;
	else
	{
		y += diff;
		entity->movement->active = false;
	}
	entity->base.y = (int)roundf(y);
}

void	img_left(t_entity *entity)
{
	float	x;
	float	diff;

	x = (float)entity->base.x;
	diff = x - entity->movement->tar.x;
	if (diff > entity->move_speed)
		x -= entity->move_speed;
	else
	{
		x -= diff;
		entity->movement->active = false;
	}
	entity->base.x = (int)roundf(x);
}

void	entity_up(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y - 1) * game->map->width) + entity->pos.x;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	entity->movement->anim = entity->up;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->roll_l;
		move_it(game, entity, UP);
		entity->pos.y--;
	}
	else
	{
		entity->movement->active = false;
	}
	entity->next = entity->movement->anim;
}

void	entity_right(t_game *game, t_entity *entity)
{
	int	dest;

	dest = (entity->pos.y * game->map->width) + entity->pos.x + 1;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->right;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->roll_r;
		move_it(game, entity, RIGHT);
		entity->pos.x++;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
}

void	entity_down(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y + 1) * game->map->width) + entity->pos.x;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	entity->movement->anim = entity->down;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->roll_r;
		move_it(game, entity, DOWN);
		entity->pos.y++;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
}

void	entity_left(t_game *game, t_entity *entity)
{
	int	dest;

	dest = (entity->pos.y * game->map->width) + entity->pos.x - 1;
	entity->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	entity->movement->anim = entity->left;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->roll_l;
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
	tar.z = entity->movement->tar.z;
	entity->movement->tar = tar;
	entity->movement->to = to;
	entity->movement->el = entity->facing;
}