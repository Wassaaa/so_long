/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:12:18 by aklein            #+#    #+#             */
/*   Updated: 2024/02/19 03:16:53 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	start_mlx(t_game *game)
{
	int	width;
	int	height;
	
	width = game->map->width * game->tile_size;
	height = game->map->height * game->tile_size;
	game->mlx = mlx_init(width, height, "2D Game", true);
	if (!game->mlx)
		error();
}

void	init_player(t_game *game)
{
	game->p = ft_calloc(1, sizeof(t_player));
	game->p->last_move = 'r';
}

t_game	*init_game(void)
{
	t_game	*game;

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game = ft_calloc(1, sizeof(t_game));
	game->map = ft_calloc(1, sizeof(t_map));
	game->movement = ft_calloc(1, sizeof(t_movement));
	init_player(game);
	srand((unsigned long)game->map * (unsigned long)game);
	return (game);
}