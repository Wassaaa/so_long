/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:23:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	check_collision(t_game *game)
{
	t_entity	*enemy;
	t_list		*enemies;

	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_entity *)enemies->content;
		if (enemy)
		{
			if (enemy->pos.x == game->p->pos.x
				&& enemy->pos.y == game->p->pos.y)
				game->game_status = -1;
		}
		enemies = enemies->next;
	}
}

void	my_loop(void *my_game)
{
	t_game	*game;

	game = (t_game *)my_game;
	show_fps(game);
	move_enemy(game);
	move_player(game);
	if (!GOD_MODE)
		check_collision(game);
	roll_animations(game);
}

int32_t	main(void)
{
	t_game	*game;

	game = init_game();
	map_info(game, "./maps/map.ber");
	fix_sizes(game);
	start_mlx(game);
	load_map_textures(game);
	map_valdiation(game, "./maps/map.ber");
	get_animations(game);
	draw_map(game);
	entity_speed(game);
	game_ui(game);
	mlx_loop_hook(game->mlx, my_loop, game);
	mlx_loop(game->mlx);
	error(EXIT_SUCCESS, 0);
	return (EXIT_SUCCESS);
}
