/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 21:54:33 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

// void	toggle_move(t_game *game)
// {
// 	// toggle_states(game, game->p->char_anims, game->movement->anim);
// 	// toggle_states(game, game->g->char_anims, game->movement->anim_g);
// 	//game->movement->anim_g->cur_f = game->movement->anim->cur_f;
// }

void	do_move(t_game *game)
{
	//toggle_move(game);
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
	static int		random;


	i += game->mlx->delta_time;
	random++;
	fps++;
	if (i >= 1)
	{
		game->fps = fps;
		if (game->fps < 30)
			game->fps = 60;
		ft_printf("\e[1;1H\e[2Jfps [%d]\n", fps);
		ft_printf("\e[2;1HMoves: [%d]\n", game->score);
		ft_printf("\e[3;1HCollectables: [%d]\n", game->map->colls);
		i = 0;
		fps = 0;
	}
	game->move_speed = (game->tile_size / game->fps) * SPEED;
	if (game->move_speed < 1)
		game->move_speed = 1 * SPEED;
	got_gun(game);
	game->random = random;
}

void	finish_prio(t_game *game)
{
	t_anim	*prio;
	t_list	*prio_list;

	if (game->prio)
	{
		prio_list = game->prio;
		while (prio_list)
		{
			prio = (t_anim *)prio_list->content;
			if (prio->cur_f != prio->frame_count - 1)
				prio->is_active = true;
			else
				prio->is_active = false;
			prio_list = prio_list->next;
		}
		ft_lstclear(&game->prio, NULL);
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
	t_anim	*next_idle;
	t_anim	*next_idle_g;
	t_list	*next_anims;
	t_list	*next_anims_g;

	next_anims = game->p->char_anims;
	next_anims_g = game->g->char_anims;
	if (game->p->last_move == 'r')
	{
		next_idle = game->p->char_idle;
		next_idle_g = game->g->char_idle;
	}
	else
	{
		next_idle = game->p->char_idle_l;
		next_idle_g = game->g->char_idle_l;
	}

	toggle_states(game, next_anims, next_idle);
	toggle_states(game, next_anims_g, next_idle_g);
}

int	win_lose(t_game *game)
{
	if (game->game_status == 1)
		ft_printf("\e[4;1H\e[JVICTORY!");
	if (game->game_status == -1)
		ft_printf("\e[4;1H\e[JYOU DIED");
	if (game->game_status != 0)
		return (1);
	return (0);
}

void	image_toggle(t_list *anims, bool onoff)
{
	t_anim	*an;
	t_list	*frames;
	mlx_image_t *img;

	while (anims)
	{
		an = anims->content;
		frames = an->frames;
		while (frames)
		{
			img = frames->content;
			img->enabled = onoff;
			frames = frames->next;
		}
		anims = anims->next;
	}
}

void	got_gun(t_game *game)
{	
	if (game->ammo < 1 && game->last_ammo >= 1)
		image_toggle(game->g->char_anims, false);
	else if(game->last_ammo < 1 && game->ammo >= 1)
		image_toggle(game->g->char_anims, true);		
	game->last_ammo = game->ammo;
}

void	find_empty_frame(t_game *game)
{
	t_list	*anims;
	t_anim	*anim;
	int		i;

	i = 0;
	anims = game->p->char_anims;
	while (anims)
	{
		anim = (t_anim *)(anims->content);
		if (anim->is_active)
			i++;
		anims = anims->next;
	}
	if (i > 0)
		ft_printf("\e[5;1H\e[J%d anims active", i);
	else
		ft_printf("bad frame");
	ft_printf("\e[6;1HRandom: [%d]\n", game->random);
}

void	my_loop(void *my_game)
{
	t_game		*game;

	game = (t_game *)my_game;
	show_fps(game);
	if (win_lose(game))
		return ;
	roll_animations(game);
	finish_prio(game);
	if (game->movement->active)
	{
		item_collection(game);
		do_move(game);
	}
	if (!game->movement->active)
	{
		do_idle(game);
		next_move(game);
	}
	find_empty_frame(game);
}

void	handle_shoot(t_game *game)
{
	t_map_element	*el;
	int				h;
	int				w;

	h = game->map->height - 1;
	w = game->map->width - 1;
	el = game->p->facing;

	if (el->type == WALL && game->ammo > 0)
	{
		if (el->x != 0 && el->y != 0 && el->y != h && el->x != w)
		{
			el->img->instances[el->instance].enabled = false;
			el->type = FREE;
			game->ammo--;
			got_gun(game);
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

int32_t	main(void)
{
	t_game		*game;

	game = init_game();
	read_map(game, "./maps/map.ber");
	fix_sizes(game);
	start_mlx(game);
	load_map_textures(game);
	read_map(game, "./maps/map.ber");
	get_animations(game);
	draw_map(game);
	mlx_loop_hook(game->mlx, my_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
