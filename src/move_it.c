/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 03:52:02 by aklein           ###   ########.fr       */
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
	int	to_x;
	int	to_y;

	to_x = (el->x * game->tile_size) + game->p->off.x;
	to_y = (el->y * game->tile_size) + game->p->off.y;
	game->movement->active = 1;
	game->movement->x = to_x;
	game->movement->y = to_y;
	game->movement->to = to;
	game->movement->el = el;
	game->score++;
}

void	go_right(t_game *game)
{
	t_map_element	*el_to_r;
	int				dest_loc;

	dest_loc = (game->map->char_y * game->map->width) + game->map->char_x + 1;
	el_to_r = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = el_to_r;
	if (move_allowed(el_to_r))
	{
		game->movement->anim = game->p->char_right;
		game->movement->anim_g = game->g->char_right;
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_right;
			game->movement->anim_g = game->g->char_roll_right;
		}
		move_to(game, el_to_r, RIGHT);
		toggle_states(game, game->g->char_anims, game->movement->anim_g);
		toggle_states(game, game->p->char_anims, game->movement->anim);
		game->map->char_x++;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
	game->p->last_move = 'r';
}

void	go_left(t_game *game)
{
	t_map_element	*el_to_l;
	int				dest_loc;
	int				random;

	random = rand() % 100;
	dest_loc = (game->map->char_y * game->map->width) + game->map->char_x - 1;
	el_to_l = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = el_to_l;
	if (move_allowed(el_to_l))
	{
		game->movement->anim = game->p->char_left;
		game->movement->anim_g = game->g->char_left;
		if (random < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_left;
			game->movement->anim_g = game->g->char_roll_left;
		}
		move_to(game, el_to_l, LEFT);
		toggle_states(game, game->g->char_anims, game->movement->anim_g);
		toggle_states(game, game->p->char_anims, game->movement->anim);
		
		game->map->char_x--;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
	game->p->last_move = 'l';
}

void	go_up(t_game *game)
{
	t_map_element	*el_to_u;
	int				dest_loc;

	dest_loc = ((game->map->char_y - 1) * game->map->width) + game->map->char_x;
	el_to_u = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = el_to_u;
	if (move_allowed(el_to_u))
	{
		game->movement->anim = game->p->char_up;
		game->movement->anim_g = game->g->char_up;
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_left;
			game->movement->anim_g = game->g->char_roll_left;
		}		
		move_to(game, el_to_u, UP);
		toggle_states(game, game->g->char_anims, game->movement->anim_g);
		toggle_states(game, game->p->char_anims, game->movement->anim);
		game->map->char_y--;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
	game->p->last_move = 'l';
}

void	go_down(t_game *game)
{
	t_map_element	*el_to_d;
	int				dest_loc;

	dest_loc = ((game->map->char_y + 1) * game->map->width) + game->map->char_x;
	el_to_d = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = el_to_d;
	if (move_allowed(el_to_d))
	{
		game->movement->anim = game->p->char_down;
		game->movement->anim_g = game->g->char_down;		
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_right;
			game->movement->anim_g = game->g->char_roll_right;
		}		
		move_to(game, el_to_d, DOWN);
		toggle_states(game, game->g->char_anims, game->movement->anim_g);
		toggle_states(game, game->p->char_anims, game->movement->anim);
		game->map->char_y++;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
	game->p->last_move = 'r';
}
