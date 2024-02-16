/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/02/16 21:30:13 by aklein           ###   ########.fr       */
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
	return (0);
}

void	move_to(t_game *game, t_map_element *el, int to)
{
	game->movement->active = 1;
	game->movement->x = el->x * game->tile_size;
	game->movement->y = el->y * game->tile_size;
	game->movement->to = to;
}

void	go_right(t_game *game)
{
	t_map_element	*el_to_r;
	int				dest_loc;

	dest_loc = (game->map->char_y * game->map->width) + game->map->char_x + 1;
	el_to_r = ft_lstget(game->map->elements, dest_loc)->content;
	if (move_allowed(el_to_r))
	{
		game->movement->anim = game->char_right;
		move_to(game, el_to_r, RIGHT);
		toggle_states(game, game->char_right);
		game->movement->anim = game->char_right;
		game->map->char_x++;
		game->map->char_y++;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
}
