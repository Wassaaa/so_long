/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:19:08 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 01:59:39 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static char	*map_file(int argc, char **argv)
{
	int		len;

	if (argc != 2)
		error(EXIT_FAILURE, E_MAP);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4))
		error(EXIT_FAILURE, E_MAP_BER);
	return (argv[1]);
}

static void	check_collision(t_game *game)
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		error(EXIT_SUCCESS, 42);
	show_fps(game);
	move_enemy(game);
	move_player(game);
	if (!GOD_MODE)
		check_collision(game);
	roll_animations(game);
}

int32_t	main(int argc, char **argv)
{
	t_game	*game;
	char	*file;

	file = map_file(argc, argv);
	game = init_game();
	map_info(game, file);
	fix_sizes(game);
	start_mlx(game);
	load_map_textures(game);
	map_valdiation(game, file);
	get_animations(game);
	draw_map(game);
	entity_speed(game);
	game_ui(game);
	mlx_loop_hook(game->mlx, my_loop, game);
	mlx_loop(game->mlx);
	error(EXIT_SUCCESS, 42);
	return (EXIT_SUCCESS);
}
