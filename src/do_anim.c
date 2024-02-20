/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:10:05 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 23:04:37 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	toggle_move(t_game *game)
{
	toggle_states(game, game->p->char_anims, game->movement->anim);
	toggle_states(game, game->g->char_anims, game->movement->anim_g);
}

void	do_move(t_game *game)
{
	if (!game->prio)
		toggle_move(game);
	if (game->movement->to == UP)
		image_up(game, game->p->char_idle->frames->content);
	else if (game->movement->to == RIGHT)
		image_right(game, game->p->char_idle->frames->content);
	else if (game->movement->to == DOWN)
		image_down(game, game->p->char_idle->frames->content);
	else if (game->movement->to == LEFT)
		image_left(game, game->p->char_idle->frames->content);
	sync_char(game);
}

void	do_idle(t_game *game)
{
	t_anim	*next_idle;
	t_anim	*next_idle_g;
	t_list	*next_anims;
	t_list	*next_anims_g;

	next_anims = game->p->char_anims;
	next_anims_g = game->g->char_anims;
	if (game->p->last_move == 'r' || game->p->last_move == 'd')
	{
		next_idle = game->p->char_idle;
		next_idle_g = game->g->char_idle;
	}
	else
	{
		next_idle = game->p->char_idle_l;
		next_idle_g = game->g->char_idle_l;
	}

	toggle_states(game, next_anims, next_idle);
	toggle_states(game, next_anims_g, next_idle_g);
}