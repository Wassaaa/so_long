/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:16:03 by aklein            #+#    #+#             */
/*   Updated: 2024/02/21 21:21:26 by aklein           ###   ########.fr       */
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

void	move_to(t_game *game, t_map_element *el, int to)
{
	int to_x;
	int to_y;

	to_x = (el->x * game->tile_size) + game->p->off.x;
	to_y = (el->y * game->tile_size) + game->p->off.y;
	game->movement->active = 1;
	game->movement->x = to_x;
	game->movement->y = to_y;
	game->movement->to = to;
	game->movement->el = el;
	game->score++;
}