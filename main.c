/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/03/01 22:11:06 by aklein           ###   ########.fr       */
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
	game->ui->scale = 1;
	if (game->mlx->width < UI_W)
	{
		game->ui->scale = (float)game->mlx->width / (float)UI_W;
		game->ui->w = game->mlx->width;
		game->ui->h *= game->ui->scale;
	}
	if (game->mlx->height < UI_H)
	{
		game->ui->scale = (float)game->mlx->height / (float)UI_H;
		game->ui->h = game->mlx->height;
		game->ui->w *= game->ui->scale;
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
	game->ui->info_y = y + (game->ui->h / 2) - (20 * game->ui->scale);
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
	ft_printf("\e[2;1HMoves: [%d]\e[K\n", game->moves);
	ft_printf("\e[3;1HCollectables: [%d]\e[K\n", game->map->colls);
}

mlx_image_t	*info_str(t_game *game, char *begin, int value, int y_off)
{
	char		*s_value;
	char		*str;
	mlx_image_t	*img;
	t_point		loc;

	s_value = ft_itoa(value);
	if (!s_value)
		error(EXIT_FAILURE, E_MALLOC);
	str = ft_strjoin(begin, s_value);
	if (!str)
		error(EXIT_FAILURE, E_MALLOC);
	loc.x = game->ui->info_x - ((ft_strlen(str) * 5 * game->ui->scale));
	loc.y = game->ui->info_y + (y_off * game->ui->scale);
	img = mlx_put_string(game->mlx, str, loc.x, loc.y);
	if (!mlx_resize_image(img, img->width * game->ui->scale, img->height * game->ui->scale))
		error(EXIT_FAILURE, E_MLX);
	free(s_value);
	free(str);
	game->ui->bg->enabled = true;
	return (img);
}

void	add_move(t_game *game)
{
	game->moves++;
	ft_printf("\e[2;1HMoves: [%d]\e[K\n", game->moves);
}

void	game_info(t_game *game)
{
	static int	box = 0;

	if (!box)
	{
		get_ui(game);
		box = 1;
	}
	got_gun(game);
}

void	my_loop(void *my_game)
{
	t_game		*game;

	game = (t_game *)my_game;
	show_fps(game);
	enemy_anim(game);
	player_anim(game);
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
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
