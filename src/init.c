/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:12:18 by aklein            #+#    #+#             */
/*   Updated: 2024/02/27 02:20:37 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	start_mlx(t_game *game)
{
	int	width;
	int	height;

	width = game->map->width * game->tile_size;
	height = game->map->height * game->tile_size;
	game->mlx = mlx_init(width, height, "Animated Gun-game", true);
	if (!game->mlx)
		error();
}

void	init_entities(t_game *game)
{
	game->p = safe_ft_calloc(1, sizeof(t_entity));
	game->p->movement = safe_ft_calloc(1, sizeof(t_movement));
	game->g = safe_ft_calloc(1, sizeof(t_entity));
	game->g->movement = safe_ft_calloc(1, sizeof(t_movement));
	game->e = safe_ft_calloc(1, sizeof(t_entity));
}

t_game **get_game(void)
{
	static t_game	*game;
	static int		initialized = 0;

	if (!initialized)
	{
		game = safe_ft_calloc(1, sizeof(t_game));
		initialized = 1;
	}
	return (&game);
}

t_game	*init_game(void)
{
	t_game	*game;

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game = *get_game();
	game->map = safe_ft_calloc(1, sizeof(t_map));
	game->ammo = 0;
	game->last_ammo = 1;
	game->z = 3;
	init_entities(game);
	return (game);
}