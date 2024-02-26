/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:47:27 by aklein            #+#    #+#             */
/*   Updated: 2024/02/26 22:03:13 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	entity_speed(t_game *game)
{
	float	scale;
	t_list		*enemies;
	t_entity	*enemy;

	scale = game->scale;
	game->p->move_speed = (int)((float)SPEED * scale);
	if (game->p->move_speed < MIN_SPEED)
		game->p->move_speed = MIN_SPEED;
	game->g->move_speed = game->p->move_speed;
	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_entity *)enemies->content;
		enemy->move_speed = game->p->move_speed / 2.0f;
		enemies = enemies->next;
	}
}

void	scale_sizes(t_game *game, float change)
{
	game->char_size = PLAYER_SIZE * change;
	game->p->off.x = PLAYER_X_OFF * change;
	game->p->off.y = PLAYER_Y_OFF * change;
	game->e->off.x = PLAYER_X_OFF * change;
	game->e->off.y = PLAYER_Y_OFF * change;
	game->map->coll_off_x = COLL_X_OFF * change;
	game->map->coll_off_y = COLL_Y_OFF * change;
	game->tile_size = TILE_SIZE * change;
	game->coll_size = COLL_SIZE * change;
	game->exit_size = EXIT_SIZE * change;
	game->scale = change;
}

void	fix_sizes(t_game *game)
{
	int		limiter;
	int		width;
	int 	height;
	float	change;

	width = game->map->width;
	height = game->map->height;
	if (width > height)
		limiter = width;
	else
		limiter = height;
	if (limiter * TILE_SIZE > WIDTH)
		game->tile_size = WIDTH / limiter;
	else
		game->tile_size = TILE_SIZE;
	change = (float)game->tile_size / (float)TILE_SIZE;
	scale_sizes(game, change);
}