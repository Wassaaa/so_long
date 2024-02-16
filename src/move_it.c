/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/02/16 21:41:55 by aklein           ###   ########.fr       */
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
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
}

void	go_left(t_game *game)
{
	t_map_element	*el_to_l;
	int				dest_loc;

	dest_loc = (game->map->char_y * game->map->width) + game->map->char_x - 1;
	el_to_l = ft_lstget(game->map->elements, dest_loc)->content;
	if (move_allowed(el_to_l))
	{
		game->movement->anim = game->char_left;
		move_to(game, el_to_l, LEFT);
		toggle_states(game, game->char_left);
		game->movement->anim = game->char_left;
		game->map->char_x--;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
}

void	go_up(t_game *game)
{
	t_map_element	*el_to_u;
	int				dest_loc;

	dest_loc = ((game->map->char_y - 1) * game->map->width) + game->map->char_x;
	el_to_u = ft_lstget(game->map->elements, dest_loc)->content;
	if (move_allowed(el_to_u))
	{
		game->movement->anim = game->char_up;
		move_to(game, el_to_u, UP);
		toggle_states(game, game->char_up);
		game->movement->anim = game->char_up;
		game->map->char_y--;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
}

void	go_down(t_game *game)
{
	t_map_element	*el_to_d;
	int				dest_loc;

	dest_loc = ((game->map->char_y + 1) * game->map->width) + game->map->char_x;
	el_to_d = ft_lstget(game->map->elements, dest_loc)->content;
	if (move_allowed(el_to_d))
	{
		game->movement->anim = game->char_down;
		move_to(game, el_to_d, DOWN);
		toggle_states(game, game->char_down);
		game->movement->anim = game->char_down;
		game->map->char_y++;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
}
