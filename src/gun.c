/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:12:02 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 03:08:24 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	gun_picked_up(t_game *game)
{
	game->map->colls--;
	ft_printf("\e[3;1HCollectables: [%d]\e[K\n", game->map->colls);
	game->ammo++;
	got_gun(game);
}

static void	image_toggle(t_entity *ent, bool onoff)
{
	t_list		*frames;
	mlx_image_t	*img;
	int			i;

	i = 0;
	while (i < A_COUNT)
	{
		frames = ent->anims[i]->frames;
		while (frames)
		{
			img = (mlx_image_t *)frames->content;
			img->enabled = onoff;
			frames = frames->next;
		}
		i++;
	}
}

void	got_gun(t_game *game)
{
	if (game->ammo < 1 && game->last_ammo >= 1)
		image_toggle(game->g, false);
	else if (game->last_ammo < 1 && game->ammo >= 1)
		image_toggle(game->g, true);
	game->last_ammo = game->ammo;
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
			game->rocks++;
			got_gun(game);
		}
	}
}

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
