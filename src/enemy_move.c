/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:14:23 by aklein            #+#    #+#             */
/*   Updated: 2024/02/22 03:25:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	img_up(t_game *game, t_enemy *enemy)
{
	int	y;

	y = enemy->base->instances[0].y;
	if (y - enemy->movement->tar.y > game->move_speed)
		y = game->move_speed;
	else
	{
		y = y - enemy->movement->tar.y;
		ft_bzero(enemy->movement, sizeof(t_movement));
	}
	enemy->base->instances[0].y -= y;
}

void	img_right(t_game *game, t_enemy *enemy)
{
	int	x;

	x = enemy->base->instances[0].x;
	if (enemy->movement->tar.x - x > game->move_speed)
		x = game->move_speed;
	else
	{
		x = enemy->movement->tar.x - x;
		ft_bzero(enemy->movement, sizeof(t_movement));
	}
	enemy->base->instances[0].x += x;
}

void	img_down(t_game *game, t_enemy *enemy)
{
	int	y;

	y = enemy->base->instances[0].y;
	if (enemy->movement->tar.y - y > game->move_speed)
		y = game->move_speed;
	else
	{
		y = enemy->movement->tar.y - y;
		ft_bzero(enemy->movement, sizeof(t_movement));
	}
	enemy->base->instances[0].y += y;
}

void	img_left(t_game *game, t_enemy *enemy)
{
	int	x;

	x = enemy->base->instances[0].x;
	if (x - enemy->movement->tar.x > game->move_speed)
		x = game->move_speed;
	else
	{
		x = x - enemy->movement->tar.x;
		ft_bzero(enemy->movement, sizeof(t_movement));
	}
	enemy->base->instances[0].x -= x;
}

void	enemy_up(t_game *game, t_enemy *enemy)
{
	int	dest;

	dest = (enemy->pos.y - 1) * game->map->width + enemy->pos.x;
	enemy->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	enemy->movement->anim = enemy->up;
	enemy->next = enemy->movement->anim;
	if (move_allowed(enemy->facing))
	{
		enemy->movement->active = true;
		enemy->movement->tar.x = enemy->pos.x * game->tile_size + enemy->off.x;
		enemy->movement->tar.y = enemy->pos.y * game->tile_size + enemy->off.y;
		enemy->movement->to = UP;
		enemy->movement->el = enemy->facing;
		enemy->pos.y--;
	}
	else
		ft_bzero(enemy->movement, sizeof(t_movement));
}

void	enemy_right(t_game *game, t_enemy *enemy)
{
	int	dest;

	dest = enemy->pos.y * game->map->width + enemy->pos.x + 1;
	enemy->facing = (t_map_element *)ft_lstget(game->map->elements, dest)->content;
	enemy->movement->anim = enemy->right;
	enemy->next = enemy->movement->anim;
	if (move_allowed(enemy->facing))
	{
		enemy->movement->active = true;
		enemy->movement->tar.x = enemy->pos.x * game->tile_size + enemy->off.x;
		enemy->movement->tar.y = enemy->pos.y * game->tile_size + enemy->off.y;
		enemy->movement->to = RIGHT;
		enemy->movement->el = enemy->facing;
		enemy->pos.x++;
	}
	else
		ft_bzero(enemy->movement, sizeof(t_movement));
}

void	enemy_down(t_game *game, t_enemy *enemy)
{
	int	dest;

	dest = (enemy->pos.y + 1) * game->map->width + enemy->pos.x;
	enemy->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	enemy->movement->anim = enemy->down;
	enemy->next = enemy->movement->anim;
	if (move_allowed(enemy->facing))
	{
		enemy->movement->active = true;
		enemy->movement->tar.x = enemy->pos.x * game->tile_size + enemy->off.x;
		enemy->movement->tar.y = enemy->pos.y * game->tile_size + enemy->off.y;
		enemy->movement->to = DOWN;
		enemy->movement->el = enemy->facing;
		enemy->pos.y++;
	}
	else
		ft_bzero(enemy->movement, sizeof(t_movement));
}

void	enemy_left(t_game *game, t_enemy *enemy)
{
	int	dest;

	dest = enemy->pos.y * game->map->width + enemy->pos.x - 1;
	enemy->facing = (t_map_element *)ft_lstget(game->map->elements,	dest)->content;
	enemy->movement->anim = enemy->left;
	enemy->next = enemy->movement->anim;
	if (move_allowed(enemy->facing))
	{
		enemy->movement->active = true;
		enemy->movement->tar.x = enemy->pos.x * game->tile_size + enemy->off.x;
		enemy->movement->tar.y = enemy->pos.y * game->tile_size + enemy->off.y;
		enemy->movement->to = LEFT;
		enemy->movement->el = enemy->facing;
		enemy->pos.x--;
	}
	else
		ft_bzero(enemy->movement, sizeof(t_movement));
}
