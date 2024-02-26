/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:07:53 by aklein            #+#    #+#             */
/*   Updated: 2024/02/26 23:11:49 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	fix_depth(t_entity *ent, int *z)
{
	mlx_image_t	*frame;
	t_anim		*anim;
	t_list		*frames;
	int			i;

	i = 0;
	while (i < A_COUNT)
	{
		anim = ent->anims[i];
		if (!anim)
		{
			i++;
			break ;
		}
		frames = anim->frames;
		while (frames)
		{
			frame = (mlx_image_t *)frames->content;
			mlx_set_instance_depth(&frame->instances[anim->instance], *z);
			frames = frames->next;
		}
		i++;
		*z = *z + 2;
	}
}

void	build_anims(t_entity *base_entity, t_entity *ent)
{
	int	i;
	int	random_frame;

	i = 0;
	while (i < A_COUNT)
	{
		if (base_entity->anims[i])
		{
			ent->anims[i] = ft_calloc(1, sizeof(t_anim));
			if (!ent->anims[i])
				error();
			*ent->anims[i] = *base_entity->anims[i];
			random_frame = get_random() % (ent->anims[i]->frame_count - 1);
			ent->anims[i]->cur_f = random_frame;
		}
		i++;
	}
}

void	draw_anims(mlx_t *mlx, t_entity *ent, int x, int y)
{
	mlx_image_t	*img;
	t_list		*frames;
	int			i;

	i = 0;
	while (i < A_COUNT)
	{
		if (!ent->anims[i])
		{
			i++;
			continue ;
		}
		frames = ent->anims[i]->frames;
		while (frames)
		{
			img = (mlx_image_t *)frames->content;
			ent->anims[i]->instance = mlx_image_to_window(mlx, img, x, y);
			img->instances[ent->anims[i]->instance].enabled = false;
			frames = frames->next;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	t_map_element	*el;
	t_list			*tile;

	tile = game->map->elements;
	while (tile)
	{
		el = (t_map_element *)tile->content;
		if (el->type == WALL)
			draw_wall(game, el);
		if (el->type == FREE)
			draw_free(game, el);
		if (el->type == PLAYER)
			draw_player(game, el);
		if (el->type == ENEMY)
			draw_enemy(game, el);
		if (el->type == COLL)
			draw_coll(game, el);
		if (el->type == EXIT)
			draw_exit(game, el);
		tile = tile->next;
	}
	fix_depth(game->e, &game->z);
	fix_depth(game->p, &game->z);
	draw_gun_anim(game);
}
