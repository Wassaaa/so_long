/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:51:56 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 03:46:07 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	start_movement(t_game *game, t_entity *entity)
{
	t_point	tar;

	entity->movement->active = true;
	tar.x = (entity->facing->x * game->tile_size) + entity->off.x;
	tar.y = (entity->facing->y * game->tile_size) + entity->off.y;
	entity->movement->tar = tar;
}

void	ent_up(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y - 1) * game->map->width) + entity->pos.x;
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_UP];
	entity->movement->to = UP;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_L];
			add_move(game);
		}
		start_movement(game, entity);
		entity->pos.y--;
	}
	else
	{
		entity->movement->active = false;
	}
	entity->next = entity->movement->anim;
	dest = (entity->pos.y * game->map->width) + entity->pos.x;
	entity->current_el = ft_lstget(game->map->elements, dest)->content;
}

void	ent_right(t_game *game, t_entity *entity)
{
	int	dest;

	dest = (entity->pos.y * game->map->width) + entity->pos.x + 1;
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_RIGHT];
	entity->movement->to = RIGHT;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_R];
			add_move(game);
		}
		start_movement(game, entity);
		entity->pos.x++;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
	dest = (entity->pos.y * game->map->width) + entity->pos.x;
	entity->current_el = ft_lstget(game->map->elements, dest)->content;
}

void	ent_down(t_game *game, t_entity *entity)
{
	int	dest;

	dest = ((entity->pos.y + 1) * game->map->width) + entity->pos.x;
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_DOWN];
	entity->movement->to = DOWN;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_R];
			add_move(game);
		}
		start_movement(game, entity);
		entity->pos.y++;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
	dest = (entity->pos.y * game->map->width) + entity->pos.x;
	entity->current_el = ft_lstget(game->map->elements, dest)->content;
}

void	ent_left(t_game *game, t_entity *entity)
{
	int	dest;

	dest = (entity->pos.y * game->map->width) + entity->pos.x - 1;
	entity->facing = ft_lstget(game->map->elements, dest)->content;
	entity->movement->anim = entity->anims[A_LEFT];
	entity->movement->to = LEFT;
	if (move_allowed(entity->facing))
	{
		if (entity == game->p)
		{
			if (get_random() % 100 < ROLL_CHANCE)
				entity->movement->anim = entity->anims[A_ROLL_L];
			add_move(game);
		}
		start_movement(game, entity);
		entity->pos.x--;
	}
	else
		entity->movement->active = false;
	entity->next = entity->movement->anim;
	dest = (entity->pos.y * game->map->width) + entity->pos.x;
	entity->current_el = ft_lstget(game->map->elements, dest)->content;
}
