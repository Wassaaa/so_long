/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/03/05 04:48:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	move_image(t_entity *entity, float dt)
{
	static t_img_move	move[4] = {img_up, img_right, img_down, img_left};

	move[entity->movement->to](entity, dt);
	sync_anim(entity);
}

void keep_direction(t_game *game, t_entity *entity)
{
	entity_move_to(game, entity);
	if (!entity->movement->active)
	{
		entity->movement->to = get_random() % 4;
		entity_move_to(game, entity);
	}
}

void	anim_off(t_anim *anim)
{
	mlx_image_t *frame;
	t_list		*frames;

	frames = anim->frames;
	while (frames)
	{
		frame = (mlx_image_t *)frames->content;
		frame->instances[anim->instance].enabled = false;
		frames = frames->next;
	}
	anim->is_active = false;
}

void	handle_next_move(t_entity *entity)
{
	if (entity->current && entity->current->full_cycle)
	{
		if (entity->current->cur_f != 0)
			entity->next = NULL;
		else
		{
			anim_off(entity->current);
			entity->current = entity->next;
		}
	}
	else if (entity->next != entity->current)
	{
		if (entity->current)
			anim_off(entity->current);
		entity->current = entity->next;
	}
	sync_anim(entity);
	entity->next = NULL;
	entity->current->is_active = true;
}

void	enemy_anim(t_game *game)
{
	t_list	*enemies;
	t_entity *enemy;

	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_entity *)enemies->content;
		if (!enemy->movement->active && !win_lose(game))
			keep_direction(game, enemy);
		if (enemy->next)
			handle_next_move(enemy);
		if (enemy->movement->active)
			move_image(enemy, game->mlx->delta_time);
		enemies = enemies->next;
	}
}

void	get_gun_next(t_game *game, t_anim *p_next)
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

void	player_anim(t_game *game)
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
		handle_next_move(game->p);
		handle_next_move(game->g);
	}
	if (player->movement && player->movement->active)
	{
		item_collection(game);
		move_image(game->p, game->mlx->delta_time);
		move_image(game->g, game->mlx->delta_time);
	}
}

void	entity_move_to(t_game *game, t_entity *entity)
{
	static t_move	move[4] = {ent_up, ent_right, ent_down, ent_left};

	move[entity->movement->to](game, entity);
}

void	check_collision(t_game *game)
{
	t_entity		*enemy;
	t_list		*enemies;

	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_entity *)enemies->content;
		if (enemy)
		{
			if (enemy->pos.x == game->p->pos.x && enemy->pos.y == game->p->pos.y)
				game->game_status = -1;
		}
		enemies = enemies->next;
	}
}

size_t get_random(void)
{
	int			fd;
	static int	not_so_random = 0;
	size_t		buff;

	not_so_random++;
	buff = not_so_random;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd > -1)
	{
		read(fd, &buff, sizeof(size_t));
		close(fd);
	}
	return (buff);
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

void	get_ui(t_game *game)
{
	mlx_texture_t	*tex;
	int				x;
	int				y;

	fix_ui_sizes(game);
	x = (game->mlx->width / 2) - (game->ui->w / 2);
	y = game->tile_size / 10;
	game->ui->info_x = x + (game->ui->w / 2);
	game->ui->info_y = y + (game->ui->h / 2) - (20 * game->ui->sc);
	tex = mlx_load_png("./textures/ui/banner.png");
	if (!tex)
		error(EXIT_FAILURE, E_MLX);
	game->ui->bg = mlx_texture_to_image(game->mlx, tex);
	if (!game->ui->bg)
		error(EXIT_FAILURE, E_MLX);
	if (!mlx_resize_image(game->ui->bg, game->ui->w, game->ui->h))
		error(EXIT_FAILURE, E_MLX);
	if (mlx_image_to_window(game->mlx, game->ui->bg, x, y) == -1)
		error(EXIT_FAILURE, E_MLX);
	game->ui->bg->enabled = false;
	mlx_delete_texture(tex);
	ft_printf("\e[2;1HMoves: [%d]\e[K\n", game->moves);
	ft_printf("\e[3;1HCollectables: [%d]\e[K\n", game->map->colls);
}

mlx_image_t	*info_str(t_game *game, char *str, int y_off)
{
	mlx_image_t	*img;
	t_point		loc;
	int			height;
	int			width;

	loc.x = game->ui->info_x - ((ft_strlen(str) * 10 * game->ui->sc));
	loc.y = game->ui->info_y + (y_off * game->ui->sc);
	img = mlx_put_string(game->mlx, str, loc.x, loc.y);
	if (!img)
		error(EXIT_FAILURE, E_MLX);
	height = img->height;
	width = img->width;
	if (!mlx_resize_image(img, width * game->ui->sc, height * game->ui->sc))
		error(EXIT_FAILURE, E_MLX);
	return (img);
}

void	add_move(t_game *game)
{
	game->moves++;
	ft_printf("\e[2;1HMoves: [%d]\e[K\n", game->moves);
	display_number(game, game->moves, game->ui->moves_loc);
}

void	scale_numbers(t_game *game)
{
	int		i;
	int		width;
	int		height;
	float	sc;

	i = 0;
	sc = game->ui->sc;
	while (i < 10)
	{
		width = game->ui->numbers[i]->width;
		height = game->ui->numbers[i]->height;
		if (!mlx_resize_image(game->ui->numbers[i], width * sc, height * sc))
			error(EXIT_FAILURE, E_MLX);
		i++;
	}
}

void	game_info(t_game *game)
{
	static int	box = 0;

	if (!box)
	{
		box = 1;
		get_ui(game);
		game->ui->bg->enabled = true;
		game->ui->moves = info_str(game, "Moves:", 0);
		generate_number_imgs(game);
	}
	game->ui->moves_loc.x = game->ui->moves->instances[0].x + game->ui->moves->width;
	game->ui->moves_loc.y = game->ui->moves->instances[0].y;
	scale_numbers(game);
	got_gun(game);
	display_number(game, game->moves, game->ui->moves_loc);
}

void	my_loop(void *my_game)
{
	t_game		*game;

	game = (t_game *)my_game;
	show_fps(game);
	enemy_anim(game);
	player_anim(game);
	if (!GOD_MODE)
		check_collision(game);
	roll_animations(game);
}

int32_t	main(void)
{
	t_game		*game;

	game = init_game();
	check_rectangle(game, "./maps/map.ber");
	fix_sizes(game);
	start_mlx(game);
	load_map_textures(game);
	map_valdiation(game, "./maps/map.ber");
	get_animations(game);
	draw_map(game);
	entity_speed(game);
	game_info(game);
	mlx_loop_hook(game->mlx, my_loop, game);
	mlx_loop(game->mlx);
	error(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
