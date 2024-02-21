/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/02/21 16:03:52 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	enemy_anim(t_game *game)
{
	t_list	*enemies;
	t_enemy *enemy;

	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_enemy *)enemies->content;
		enemy->current = enemy->move_right;
		toggle_states(game, enemy->enemy_anims, enemy->current);
		enemies = enemies->next;
	}
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
	//enemy_anim(game);
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
