/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/03/01 00:04:27 by aklein           ###   ########.fr       */
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
	ft_printf("\e[5;1H\e[Jrandom is: %u", buff);
	return (buff);
}

void	get_ui(t_game *game)
{
	mlx_image_t		*img;
	mlx_texture_t	*tex;
	int				x;
	int				y;

	x = game->tile_size / 10;
	y = game->tile_size / 10;
	game->ui->info_x = x + (UI_W / 2);
	game->ui->info_y = y + (UI_H / 2) - 20;
	tex = mlx_load_png("./textures/ui/banner.png");
	if (!tex)
		error(EXIT_FAILURE, E_MLX);
	img = mlx_texture_to_image(game->mlx, tex);
	if (!img)
		error(EXIT_FAILURE, E_MLX);
	if (!mlx_resize_image(img, UI_W, UI_H))
		error(EXIT_FAILURE, E_MLX);
	if (mlx_image_to_window(game->mlx, img, x, y) < 0)
		error(EXIT_FAILURE, E_MLX);
}

void	draw_info(t_game *game)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	x = game->ui->info_x;
	y = game->ui->info_y;
	img = game->ui->info_img;
	if (img)
		mlx_delete_image(game->mlx, img);
	img = mlx_put_string(game->mlx, game->ui->info_txt, x, y);
	if (!img)
		error(EXIT_FAILURE, E_MLX);
	game->ui->info_img = img;
	img = NULL;
}

void	info_str(t_game *game)
{
	char	*score;
	char	*ammo;
	char	*moves_part;
	char	*nl_part;

	score = ft_itoa(game->score);
	game->ui->info_x += ft_strlen(score) / 2;
	ammo = ft_itoa(game->ammo);
	moves_part = ft_strjoin("Moves: ", score);
	if (!moves_part)
		error(EXIT_FAILURE, E_MALLOC);
	nl_part = ft_strjoin(moves_part, "\nAmmo: ");
	if (!nl_part)
		error(EXIT_FAILURE, E_MALLOC);
	game->ui->info_txt = ft_strjoin(nl_part, ammo);
	free(moves_part);
	free(nl_part);
	free(score);
	free(ammo);
}

void	game_info(t_game *game)
{
	static int		box = 0;

	if (!box)
	{
		get_ui(game);
		box = 1;
	}
	info_str(game);
	draw_info(game);
}

void	my_loop(void *my_game)
{
	t_game		*game;

	game = (t_game *)my_game;
	game_info(game);
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
	mlx_loop_hook(game->mlx, my_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
