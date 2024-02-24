/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:47:27 by aklein            #+#    #+#             */
/*   Updated: 2024/02/24 01:04:06 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	scale_sizes(t_game *game, float change)
{
	game->fps = 60;
	game->char_size = CHAR_SIZE * change;
	game->p->off.x = CHAR_X_OFF * change;
	game->p->off.y = CHAR_Y_OFF * change;
	game->e->off.x = CHAR_X_OFF * change;
	game->e->off.y = CHAR_Y_OFF * change;
	game->map->coll_off_x = COLL_X_OFF * change;
	game->map->coll_off_y = COLL_Y_OFF * change;
	game->tile_size = TILE_SIZE * change;
	game->coll_size = COLL_SIZE * change;
	game->exit_size = EXIT_SIZE * change;
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