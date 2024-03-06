/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:51:56 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 01:02:48 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	start_movement(t_game *game, t_entity *entity, int to)
{
	t_point	tar;

	entity->movement->active = true;
	tar.x = (entity->facing->x * game->tile_size) + entity->off.x;
	tar.y = (entity->facing->y * game->tile_size) + entity->off.y;
	entity->movement->tar = tar;
	entity->movement->to = to;
}

void	ent_up(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y - 1) * game->map->width) + entity->pos.x;
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_UP];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_L];
			add_move(game);
		}
		start_movement(game, entity, UP);
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
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_RIGHT];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_R];
			add_move(game);
		}
		start_movement(game, entity, RIGHT);
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
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_DOWN];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_R];
			add_move(game);
		}
		start_movement(game, entity, DOWN);
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
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_LEFT];
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_L];
			add_move(game);
		}
		start_movement(game, entity, LEFT);
		entity->pos.x--;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
}
