/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 04:06:11 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	build_wall(t_game *game)
{
	t_map_element	*el;

	el = game->p->current_el;
	if (el->type == FREE && game->rocks > 0)
	{
		el->images = game->wall_imgs;
		draw_wall(game, el);
		game->rocks--;
		el->type = WALL;
	}
}

static void	next_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		handle_shoot(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL))
		build_wall(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		ent_right(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ent_down(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		ent_left(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ent_up(game, game->p);
}

static void	get_gun_next(t_game *game, t_anim *p_next)
{
	t_anim		**anims;
	int			i;

	i = 0;
	anims = game->p->anims;
	*game->g->movement = *game->p->movement;
	game->g->base = game->p->base;
	sync_anim(game->g);
	while (i < A_COUNT)
	{
		if (anims[i] == p_next)
			break ;
		i++;
	}
	game->g->next = game->g->anims[i];
}

static void	do_idle(t_game *game)
{
	if (game->p->movement->to == DOWN || game->p->movement->to == RIGHT)
		game->p->next = game->p->anims[A_IDLE_R];
	else
		game->p->next = game->p->anims[A_IDLE_L];
}

void	move_player(t_game *game)
{
	t_entity	*player;

	player = game->p;
	if (player->movement && !player->movement->active)
	{
		if (!win_lose(game))
		{
			next_move(game);
			if (!player->movement->active)
				do_idle(game);
		}
	}
	if (player->next)
	{
		get_gun_next(game, player->next);
		movement_animation(game->p);
		movement_animation(game->g);
	}
	if (player->movement && player->movement->active)
	{
		item_collection(game);
		move_image(game->p, game->mlx->delta_time);
		move_image(game->g, game->mlx->delta_time);
	}
}
