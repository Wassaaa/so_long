/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:16:03 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 01:06:50 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	move_allowed(t_map_element *el)
{
	if (el->type == WALL)
		return (0);
	if (el->type == PLAYER)
		return (1);
	if (el->type == FREE)
		return (1);
	if (el->type == COLL)
		return (1);
	if (el->type == EXIT)
		return (1);
	if (el->type == ENEMY)
		return (1);
	return (0);
}

void	add_move(t_game *game)
{
	game->moves++;
	ft_printf("\e[2;1HMoves: [%d]\e[K\n", game->moves);
	display_number(game, game->moves, game->ui->moves_loc);
}
