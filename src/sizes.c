/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:47:27 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 08:26:49 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	entity_speed(t_game *game)
{
	float		scale;
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
		enemy->move_speed = game->p->move_speed * ENEMY_MOD;
		if (enemy->move_speed < MIN_SPEED)
			enemy->move_speed = MIN_SPEED;
		enemies = enemies->next;
	}
}

void	scale_sizes(t_game *game, float change)
{
	if (change < MAX_SCALE)
		error(EXIT_FAILURE, E_MAP_SCALE);
	game->char_size = PLAYER_SIZE * change;
	game->p->off.x = PLAYER_X_OFF * change;
	game->p->off.y = PLAYER_Y_OFF * change;
	game->e->off.x = PLAYER_X_OFF * change;
	game->e->off.y = PLAYER_Y_OFF * change;
	game->map->coll_off.x = COLL_X_OFF * change;
	game->map->coll_off.y = COLL_Y_OFF * change;
	game->tile_size = TILE_SIZE * change;
	game->coll_size = COLL_SIZE * change;
	game->exit_size = EXIT_SIZE * change;
	game->scale = change;
}

void	fix_sizes(t_game *game)
{
	int		limiter;
	int		max_size;
	float	change;

	if (game->map->width > game->map->height)
	{
		limiter = game->map->width;
		max_size = WIDTH;
	}
	else
	{
		limiter = game->map->height;
		max_size = HEIGHT;
	}
	if (limiter * TILE_SIZE > max_size)
		game->tile_size = max_size / limiter;
	else
		game->tile_size = TILE_SIZE;
	change = (float)game->tile_size / (float)TILE_SIZE;
	scale_sizes(game, change);
}

void	fix_ui_sizes(t_game *game)
{
	game->ui->w = UI_W;
	game->ui->h = UI_H;
	game->ui->sc = 1;
	if (game->mlx->width < UI_W)
	{
		game->ui->sc = (float)game->mlx->width / (float)UI_W;
		game->ui->w = game->mlx->width;
		game->ui->h *= game->ui->sc;
	}
	if (game->mlx->height < UI_H)
	{
		game->ui->sc = (float)game->mlx->height / (float)UI_H;
		game->ui->h = game->mlx->height;
		game->ui->w *= game->ui->sc;
	}
	game->ui->moves_y = 0;
}
