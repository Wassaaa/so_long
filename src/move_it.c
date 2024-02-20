/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:41 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 23:11:11 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>



void	go_right(t_game *game)
{
	t_map_element	*next_el;
	int				dest_loc;

	dest_loc = (game->map->char_y * game->map->width) + game->map->char_x + 1;
	next_el = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = next_el;
	if (move_allowed(next_el))
	{
		game->movement->anim = game->p->char_right;
		game->movement->anim_g = game->g->char_right;
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_right;
			game->movement->anim_g = game->g->char_roll_right;
		}
		move_to(game, next_el, RIGHT);
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
	t_map_element	*next_el;
	int				dest_loc;

	dest_loc = (game->map->char_y * game->map->width) + game->map->char_x - 1;
	next_el = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = next_el;
	if (move_allowed(next_el))
	{
		game->movement->anim = game->p->char_left;
		game->movement->anim_g = game->g->char_left;
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_left;
			game->movement->anim_g = game->g->char_roll_left;
		}
		move_to(game, next_el, LEFT);
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
	t_map_element	*next_el;
	int				dest_loc;

	dest_loc = ((game->map->char_y - 1) * game->map->width) + game->map->char_x;
	next_el = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = next_el;
	if (move_allowed(next_el))
	{
		game->movement->anim = game->p->char_up;
		game->movement->anim_g = game->g->char_up;
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_left;
			game->movement->anim_g = game->g->char_roll_left;
		}		
		move_to(game, next_el, UP);
		toggle_states(game, game->g->char_anims, game->movement->anim_g);
		toggle_states(game, game->p->char_anims, game->movement->anim);
		game->map->char_y--;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
	game->p->last_move = 'u';
}

void	go_down(t_game *game)
{
	t_map_element	*next_el;
	int				dest_loc;

	dest_loc = ((game->map->char_y + 1) * game->map->width) + game->map->char_x;
	next_el = ft_lstget(game->map->elements, dest_loc)->content;
	game->p->facing = next_el;
	if (move_allowed(next_el))
	{
		game->movement->anim = game->p->char_down;
		game->movement->anim_g = game->g->char_down;		
		if (rand() % 100 < ROLL_CHANCE)
		{
			game->movement->anim = game->p->char_roll_right;
			game->movement->anim_g = game->g->char_roll_right;
		}		
		move_to(game, next_el, DOWN);
		toggle_states(game, game->g->char_anims, game->movement->anim_g);
		toggle_states(game, game->p->char_anims, game->movement->anim);
		game->map->char_y++;
	}
	else
		ft_bzero(game->movement, sizeof(t_movement));
	game->p->last_move = 'd';
}

void	next_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		handle_shoot(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		go_right(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		go_down(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		go_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_up(game);
}
