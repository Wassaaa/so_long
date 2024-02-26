/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/02/26 23:34:48 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	next_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		handle_shoot(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		ent_right(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ent_down(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		ent_left(game, game->p);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ent_up(game, game->p);
}
