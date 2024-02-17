/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/17 21:19:24 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	draw_map(t_game *game)
{
	t_map_element	*el;
	t_list			*tile;
	mlx_image_t		*img;
	mlx_image_t		*free_img;

	tile = game->map->elements;
	while (tile)
	{
		el = (t_map_element *)tile->content;
		free_img = ft_lstget(game->free_imgs, 0)->content;
		if (el->type == WALL)
			free_img = ft_lstget(game->free_imgs, FREE_C - 1)->content;
		mlx_image_to_window(game->mlx, free_img, el->x * game->tile_size, el->y
			* game->tile_size);
		img = ft_lstget(el->images, rand() % ft_lstsize(el->images))->content;
		if (el->type == FREE || el->type == PLAYER)
			img = ft_lstget(el->images, rand() % 3)->content;
		el->instance = mlx_image_to_window(game->mlx, img, el->x * game->tile_size,
				el->y * game->tile_size);
		tile = tile->next;
	}
}

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

void	my_loop(void *my_game)
{
	t_game		*game;
	static int	fps;

	game = (t_game *)my_game;
	fps = 1 / game->mlx->delta_time;
	ft_printf("\e[1;1H\e[2Jfps [%d]\n", fps);
	if (game->movement->active)
		do_move(game);
	else
		next_move(game);
	animation_loop(game->p->char_anims, game->mlx->delta_time);
	if (!game->p->char_idle ->is_active && !game->p->char_idle_l->is_active)
	{
		if (game->p->last_move == 'r')
			toggle_states(game, game->p->char_idle);
		else
			toggle_states(game, game->p->char_idle_l);
	}
}

void	next_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		go_right(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		go_down(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		go_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_up(game);
}

void	scale_sizes(t_game *game, float change)
{
	game->char_size = CHAR_SIZE * change;
	game->p->off.x = CHAR_X_OFF * change;
	game->p->off.y = CHAR_Y_OFF * change;
	game->tile_size = TILE_SIZE * change;
	game->coll_size = COLL_SIZE * change;
	game->move_speed = SPEED * change;
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
