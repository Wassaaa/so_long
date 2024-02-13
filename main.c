/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 23:11:17 by aklein           ###   ########.fr       */
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

void	sync_char_frames(t_game *game)
{
	int	x;
	int	y;
	mlx_image_t	*base_img;

	base_img = (mlx_image_t *)game->char_idle->frames->content;
	x = base_img->instances[0].x;
	y = base_img->instances[0].y;
	iterate_frames(game->char_idle->frames, x, y);
	iterate_frames(game->char_right->frames, x, y);
	iterate_frames(game->char_left->frames, x, y);
	iterate_frames(game->char_up->frames, x, y);
	iterate_frames(game->char_down->frames, x, y);
	iterate_frames(game->char_roll_right->frames, x, y);
	iterate_frames(game->char_roll_left->frames, x, y);
}

int	update_animation(t_anim *a, double dt)
{
	if (a)
	{
		a->accum += dt * 1000;
		if (a->accum > a->frame_speed)
		{
			a->accum -= a->frame_speed;
			a->cur_f++;
			a->cur_f %= ft_lstsize(a->frames);
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

void	turn_others_off(t_game *game, t_anim *current)
{
	game->char_idle->is_active = false;
	game->char_right->is_active = false;
	game->char_left->is_active = false;
	game->char_up->is_active = false;
	game->char_down->is_active = false;
	game->char_roll_right->is_active = false;
	game->char_roll_left->is_active = false;
	current->is_active = true;
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
	animate_character(game->char_idle, game->mlx->delta_time);
	animate_character(game->char_right, game->mlx->delta_time);
	animate_character(game->char_left, game->mlx->delta_time);
	animate_character(game->char_up, game->mlx->delta_time);
	animate_character(game->char_down, game->mlx->delta_time);
	animate_character(game->char_idle, game->mlx->delta_time);

}

t_game *init_game(mlx_t *mlx)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx;
	game->char_size = CHAR_SIZE;
	return (game);
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
	game = init_game(mlx);	
	background = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!background)
		error();
	if (mlx_image_to_window(mlx, background, 0, 0) < 0)
		error();
	ft_memset(background->pixels, 0x00000000, WIDTH * HEIGHT * BPP);
	get_animations(game);
	mlx_loop_hook(mlx, character_move, game);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
