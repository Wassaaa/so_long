/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/02/23 22:11:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	next_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		handle_shoot(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		entity_right(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		entity_down(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		entity_left(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		entity_up(game, game->p);
}
