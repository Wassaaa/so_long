/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:12:02 by aklein            #+#    #+#             */
/*   Updated: 2024/02/23 21:26:13 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	item_collection(t_game *game)
{
	int			coll_inst;
	t_entity	*player;

	player = game->p;
	if (player->facing->type == COLL)
	{
		gun_picked_up(game);
		coll_inst = player->facing->instance;
		player->facing->img->instances[coll_inst].enabled = false;
		player->facing->type = FREE;
	}
	else if (player->facing->type == EXIT)
	{
		if (game->map->colls == 0)
			game->game_status = 1;
	}
}

void	gun_picked_up(t_game *game)
{
	game->map->colls--;
	game->ammo++;
	got_gun(game);
}

void	got_gun(t_game *game)
{
	if (game->ammo < 1 && game->last_ammo >= 1)
		image_toggle(game->g->anims, false);
	else if(game->last_ammo < 1 && game->ammo >= 1)
		image_toggle(game->g->anims, true);
	game->last_ammo = game->ammo;
}

void	image_toggle(t_list *anims, bool onoff)
{
	t_anim	*anim;
	t_list	*frames;
	mlx_image_t *img;

	while (anims)
	{
		anim = anims->content;
		frames = anim->frames;
		while (frames)
		{
			img = frames->content;
			img->enabled = onoff;
			frames = frames->next;
		}
		anims = anims->next;
	}
}

void	handle_shoot(t_game *game)
{
	t_map_element	*el;
	int				h;
	int				w;

	h = game->map->height - 1;
	w = game->map->width - 1;
	el = game->p->facing;

	if (el->type == WALL && game->ammo > 0)
	{
		if (el->x != 0 && el->y != 0 && el->y != h && el->x != w)
		{
			el->img->instances[el->instance].enabled = false;
			el->type = FREE;
			game->ammo--;
			got_gun(game);
		}
	}
}

