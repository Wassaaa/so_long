/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:12:18 by aklein            #+#    #+#             */
/*   Updated: 2024/02/17 04:12:25 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	init_player(t_game *game)
{
	game->p = ft_calloc(1, sizeof(t_player));
	game->p->last_move = 'r';
	game->p->off.x = CHAR_X_OFF;
	game->p->off.y = CHAR_Y_OFF;
}

t_game	*init_game(void)
{
	t_game	*game;
	mlx_t	*mlx;

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx = mlx_init(WIDTH, HEIGHT, "2D Game", true);
	if (!mlx)
		error();
	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx;
	game->char_size = CHAR_SIZE;
	game->tile_size = TILE_SIZE;
	game->coll_size = COLL_SIZE;
	game->move_speed = SPEED;
	game->map = ft_calloc(1, sizeof(t_map));
	game->movement = ft_calloc(1, sizeof(t_movement));
	init_player(game);
	srand((unsigned long)mlx * (unsigned long)game);
	return (game);
}