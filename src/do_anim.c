/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:10:05 by aklein            #+#    #+#             */
/*   Updated: 2024/03/01 04:43:57 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	do_idle(t_game *game)
{
	if (game->p->movement->to == DOWN || game->p->movement->to == RIGHT)
		game->p->next = game->p->anims[A_IDLE_R];
	else
		game->p->next = game->p->anims[A_IDLE_L];
	if (game->moves - game->last_moves > 10)
	{
		if (game->ui->moves)
			mlx_delete_image(game->mlx, game->ui->moves);
		game->ui->moves = info_str(game, "Moves: ", game->moves, game->ui->moves_y);
		game->last_moves = game->moves;
	}
}
