/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/15 23:25:24 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	iterate_frames(t_list *lst, int x, int y)
{
	mlx_image_t *img;

	if (!lst)
		return ;
	while (lst)
	{
		img = (mlx_image_t *)lst->content;
		img->instances[0].x = x;
		img->instances[0].y = y;
		lst = lst->next;
	}
}

void	sync_anim_frames(mlx_image_t *base, t_list *anims)
{
	int		x;
	int		y;
	t_anim	*anim;

	x = base->instances[0].x;
	y = base->instances[0].y;
	while (anims != NULL)
	{
		anim = (t_anim *)anims->content;
		iterate_frames(anim->frames, x, y);
		anims = anims->next;
	}
}

int	update_animation(t_anim *a, double dt)
{
	if (a)
	{
		a->accum += dt * 1000;
		if (a->accum > a->frame_speed * 2)
			a->accum = a->frame_speed + 1;
		if (a->accum > a->frame_speed)
		{
			a->accum -= a->frame_speed;
			a->cur_f++;
			a->cur_f %= a->frame_count;
			return (1);
		}
	}
	return (0);
}

void	animate_character(t_anim *anim, double dt)
{
	mlx_image_t *img;

	img = ft_lstget(anim->frames, anim->cur_f)->content;
	img->instances[0].enabled = false;
	if (anim->is_active)
	{
		if (update_animation(anim, dt))
			if (anim->one_cycle && anim->cur_f == 0)
			{
				anim->is_active = false;
				return ;
			}
		img = ft_lstget(anim->frames, anim->cur_f)->content;
		img->instances[0].enabled = true;
	}
}

void	animation_loop(t_list *anims, double dt)
{
	t_anim	*anim;

	while (anims != NULL)
	{
		anim = (t_anim *)anims->content;
		animate_character(anim, dt);
		anims = anims->next;
	}
}

void	turn_others_off(t_game *game, t_anim *current)
{
	t_list	*temp_anims;
	t_anim	*iter;

	temp_anims = game->char_anims;
	while (temp_anims != NULL)
	{
		iter = (t_anim *)temp_anims->content;
		if (iter == current)
			iter->is_active = true;
		else
			iter->is_active = false;
		temp_anims = temp_anims->next;
	}


}

void	toggle_states(t_game *game, t_anim *current)
{
	turn_others_off(game, current);
}

void	character_move(void *my_game)
{
	t_game	*game;

	game = (t_game *)my_game;
	if (game->char_roll_right->is_active)
	{
		animate_character(game->char_roll_right, game->mlx->delta_time);
		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
			move_down(game);
		else
			move_right(game);
		return ;
	}
	if (game->char_roll_left->is_active)
	{
		animate_character(game->char_roll_left, game->mlx->delta_time);
		if (mlx_is_key_down(game->mlx, MLX_KEY_W))
			move_up(game);
		else
			move_left(game);
		return ;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		toggle_states(game, game->char_right);
		move_right(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			toggle_states(game, game->char_roll_right);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		toggle_states(game, game->char_left);
		move_left(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			toggle_states(game, game->char_roll_left);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		toggle_states(game, game->char_down);
		move_down(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			toggle_states(game, game->char_roll_right);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		toggle_states(game, game->char_up);
		move_up(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
			toggle_states(game, game->char_roll_left);
	}
	else
		toggle_states(game, game->char_idle);
	animation_loop(game->char_anims, game->mlx->delta_time);
	static int fps;
	fps = 1000 * game->mlx->delta_time;
	ft_printf("\e[1;1H\e[2Jfps [%d]\n", fps);
	// ft_printf("random: [%d]\n", rand() % 100);
}

t_game *init_game(mlx_t *mlx)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx;
	game->char_size = CHAR_SIZE;
	game->tile_size = TILE_SIZE;
	game->coll_size = COLL_SIZE;
	game->map = ft_calloc(1, sizeof(t_map));
	return (game);
}

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
		img = ft_lstget(el->images, rand() % ft_lstsize(el->images))->content;
		mlx_image_to_window(game->mlx, free_img, el->x * TILE_SIZE, el->y * TILE_SIZE);
		el->instance = mlx_image_to_window(game->mlx, img, el->x * TILE_SIZE, el->y * TILE_SIZE);
		tile = tile->next;
	}
}

int32_t	main(void)
{
	mlx_t			*mlx;
	t_game			*game;
	mlx_image_t		*background;

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();
	background = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!background)
		error();
	if (mlx_image_to_window(mlx, background, 0, 0) < 0)
		error();
	ft_memset(background->pixels, 0x00000000, WIDTH * HEIGHT * BPP);
	game = init_game(mlx);
	load_map_textures(game);
	read_map(game, "./maps/map.ber");
	draw_map(game);
	get_animations(game);
	srand((unsigned long)mlx * (unsigned long)background);
	mlx_loop_hook(mlx, character_move, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
