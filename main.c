/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/22 03:11:09 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	move_image(t_game *game, t_enemy *enemy)
{
	t_img_move	move[4];

	move[UP] = img_up;
	move[RIGHT] = img_right;
	move[DOWN] = img_down;
	move[LEFT] = img_left;
	move[enemy->movement->to](game, enemy);
	sync_anim(enemy);
}

void	enemy_anim(t_game *game)
{
	t_list	*enemies;
	t_enemy *enemy;

	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_enemy *)enemies->content;
		if (!enemy->movement->active)
		{
			enemy->movement->to = rand() % 4;
			enemy_move_to(game, enemy);
		}
		if (enemy->next && enemy->next != enemy->current)
		{
			if (enemy->current)
				enemy->current->is_active = false;
			enemy->current = enemy->next;
			enemy->current->is_active = true;
			enemy->next = NULL;
		}
		if (enemy->movement->active)
			move_image(game, enemy);
		enemies = enemies->next;
	}
}


void	enemy_move_to(t_game *game, t_enemy *enemy)
{
	if (enemy->movement->to == UP)
		enemy_up(game, enemy);
	if (enemy->movement->to == RIGHT)
		enemy_right(game, enemy);
	if (enemy->movement->to == DOWN)
		enemy_down(game, enemy);
	if (enemy->movement->to == LEFT)
		enemy_left(game, enemy);
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
	enemy_anim(game);
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
