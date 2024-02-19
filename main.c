/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/19 03:07:53 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	do_move(t_game *game)
{
	toggle_states(game, game->movement->anim);
	if (game->movement->to == UP)
		image_up(game, game->p->char_idle->frames->content);
	else if (game->movement->to == RIGHT)
		image_right(game, game->p->char_idle->frames->content);
	else if (game->movement->to == DOWN)
		image_down(game, game->p->char_idle->frames->content);
	else if (game->movement->to == LEFT)
		image_left(game, game->p->char_idle->frames->content);
	sync_char(game);
}

void	show_fps(t_game *game)
{
	static int		fps = 1;
	static double	i = 0;


	i += game->mlx->delta_time;
	fps++;
	if (i >= 1)
	{
		game->fps = fps;
		ft_printf("\e[1;1H\e[2Jfps [%d]\n", fps);
		ft_printf("\e[2;1HMoves: [%d]\n", game->score);
		ft_printf("\e[3;1HCollectables: [%d]\n", game->map->colls);
		i = 0;
		fps = 0;
	}
	game->move_speed = (game->tile_size / game->fps) * 6;
	if (game->move_speed < 1)
		game->move_speed = 1;
}

void	finish_prio(t_game *game)
{
	if (!game->prio)
		return ;
	if (game->prio->cur_f != 0)
	{
		game->prio->is_active = true;
		if (game->prio != game->next)
			game->next->is_active = false;
	}
	else
	{
		game->next->is_active = true;
		game->prio->is_active = false;
		game->prio = NULL;
		game->next = NULL;
	}
}

void	item_collection(t_game *game)
{
	int	coll_ins;

	if (game->movement->el->type == COLL)
	{
		gun_picked_up(game);
		coll_ins = game->movement->el->instance;
		game->movement->el->img->instances[coll_ins].enabled = false;
		game->movement->el->type = FREE;
	}
	else if (game->movement->el->type == EXIT)
	{
		if (game->map->colls == 0)
			game->game_status = 1;
	}
}

void	do_idle(t_game *game)
{
	if (!game->p->char_idle ->is_active && !game->p->char_idle_l->is_active)
	{
		if (game->p->last_move == 'r')
			toggle_states(game, game->p->char_idle);
		else
			toggle_states(game, game->p->char_idle_l);
	}
}

int	win_lose(t_game *game)
{
	if (game->game_status == 1)
		ft_printf("VICTORY!");
	if (game->game_status == -1)
		ft_printf("YOU DIED");
	if (game->game_status != 0)
		return (1);
	return (0);
}

void	my_loop(void *my_game)
{
	t_game		*game;

	game = (t_game *)my_game;
	show_fps(game);
	if (win_lose(game))
		return ;
	if (game->movement->active)
		do_move(game);
	else
		next_move(game);
	finish_prio(game);
	animation_loop(game->p->char_anims, game->mlx->delta_time);
	if (!game->movement->active && !game->prio)
		do_idle(game);
	if (game->movement->active)
		item_collection(game);
}

void	handle_shoot(t_game *game)
{
	t_map_element	*el;
	int				h;
	int				w;

	h = game->map->height - 1;
	w = game->map->width - 1;
	el = game->p->facing;

	if (el->type == WALL && game->p->has_gun)
	{
		if (el->x != 0 && el->y != 0 && el->y != h && el->x != w)
		{
			el->img->instances[el->instance].enabled = false;
			el->type = FREE;
		}
	}
}

void	next_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		go_right(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			handle_shoot(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		go_down(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			handle_shoot(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		go_left(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			handle_shoot(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		go_up(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			handle_shoot(game);
	}
}

void	scale_sizes(t_game *game, float change)
{
	game->char_size = CHAR_SIZE * change;
	game->p->off.x = CHAR_X_OFF * change;
	game->p->off.y = CHAR_Y_OFF * change;
	game->map->coll_off_x = COLL_X_OFF * change;
	game->map->coll_off_y = COLL_Y_OFF * change;
	game->tile_size = TILE_SIZE * change;
	game->coll_size = COLL_SIZE * change;
	game->exit_size = EXIT_SIZE * change;
	game->move_speed = SPEED * change;
	game->fps = 60;
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
	{
        limiter = height;
	}
	if (limiter * TILE_SIZE > WIDTH)
		game->tile_size = WIDTH / limiter;
	else
		game->tile_size = TILE_SIZE;
	change = (float)game->tile_size / (float)TILE_SIZE;
	scale_sizes(game, change);
}

int32_t	main(void)
{
	t_game		*game;

	game = init_game();
	read_map(game, "./maps/map.ber");
	fix_sizes(game);
	start_mlx(game);
	load_map_textures(game);
	read_map(game, "./maps/map.ber");
	draw_map(game);
	get_animations(game);
	mlx_loop_hook(game->mlx, my_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
