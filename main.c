/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 01:51:54 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

#define WIDTH 1280
#define HEIGHT 1024

#define	CHAR_SIZE 512
#define TILE_SIZE 384

void	image_forward(void *image)
{
	mlx_image_t *img;

	img = (mlx_image_t *)image;
	img->instances[0].x += 7;
}

void	image_backwards(void *image)
{
	mlx_image_t *img;

	img = (mlx_image_t *)image;
	img->instances[0].x -= 7; 
}

void	move_forward(t_game *game)
{
	ft_lstiter(game->char_move->frames, image_forward);
	ft_lstiter(game->char_idle->frames, image_forward);
	ft_lstiter(game->char_roll->frames, image_forward);
}

void	move_backwards(t_game *game)
{
	ft_lstiter(game->char_move->frames, image_backwards);
	ft_lstiter(game->char_idle->frames, image_backwards);
	ft_lstiter(game->char_roll->frames, image_backwards);

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

void	character_idle_animation(void *my_game)
{
	static int			fps;
	mlx_image_t			*img;
	t_game				*game;
	t_anim				*anim;
	t_list				*frames;

	game = (t_game *)my_game;
	anim = game->char_idle;
	frames = anim->frames;
	fps = 1000 / game->mlx->delta_time;
 	printf("\e[1;1H\e[2Jfps [%d]\n", fps);
	img = (mlx_image_t *)ft_lstget(frames, anim->cur_f)->content;
	img->instances[0].enabled = false;
	if (anim->is_active)
	{
		update_animation((t_anim *)anim, game->mlx->delta_time);
		img = (mlx_image_t *)ft_lstget(frames, anim->cur_f)->content;
		img->instances[0].enabled = true;
	}
}

void	character_move_animation(void *my_game)
{
	mlx_image_t			*img;
	t_game				*game;
	t_anim				*anim;
	t_list				*frames;

	game = (t_game *)my_game;
	anim = game->char_move;
	frames = anim->frames;
	img = (mlx_image_t *)ft_lstget(frames, anim->cur_f)->content;
	img->instances[0].enabled = false;
	if (anim->is_active)
	{
		update_animation((t_anim *)anim, game->mlx->delta_time);
		img = (mlx_image_t *)ft_lstget(frames, anim->cur_f)->content;
		img->instances[0].enabled = true;
	}
}

void	character_roll_animation(void *my_game)
{
	mlx_image_t			*img;
	t_game				*game;
	t_anim				*anim;
	t_list				*frames;

	game = (t_game *)my_game;
	anim = game->char_roll;
	frames = anim->frames;
	img = (mlx_image_t *)ft_lstget(frames, anim->cur_f)->content;
	img->instances[0].enabled = false;
	if (anim->is_active)
	{
		if (update_animation((t_anim *)anim, game->mlx->delta_time))
		{
			if (anim->cur_f == 0)
			{
				anim->is_active = false;
				return ;
			}			
		}
		img = (mlx_image_t *)ft_lstget(frames, anim->cur_f)->content;
		img->instances[0].enabled = true;
	}
}

void	character_move(void *my_game)
{
	t_game	*game;

	game = (t_game *)my_game;
	if (game->char_roll->is_active)
	{
		character_roll_animation(game);
		move_forward(game);
		return ;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->char_idle->is_active = false;
		game->char_move->is_active = true;
		move_forward(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		{
			game->char_idle->is_active = false;
			game->char_move->is_active = false;
			game->char_roll->is_active = true;
		}
	}	
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->char_idle->is_active = false;
		game->char_move->is_active = true;
		move_backwards(game);
		if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		{
			game->char_idle->is_active = false;
			game->char_move->is_active = false;
			game->char_roll->is_active = true;
		}
	}
	else
	{
		game->char_idle->is_active = true;
		game->char_move->is_active = false;
	}
	character_move_animation(game);


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
	ft_memset(background->pixels, 0xFFFFFFFF, WIDTH * HEIGHT * BPP);
	get_animations(game);
	mlx_loop_hook(mlx, character_idle_animation, game);
	mlx_loop_hook(mlx, character_move, game);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
