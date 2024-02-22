/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:46:24 by aklein            #+#    #+#             */
/*   Updated: 2024/02/22 03:10:46 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	iterate_frames(t_list *lst, int x, int y)
{
	mlx_image_t *img;

	if (!lst)
		return ;
	while (lst)
	{
		img = (mlx_image_t *)lst->content;
		img->instances[0].x = x;
		img->instances[0].y = y;
		lst = lst->next;
	}
}

void	sync_anim_frames(mlx_image_t *base, t_list *anims)
{
	int		x;
	int		y;
	t_anim	*anim;

	x = base->instances[0].x;
	y = base->instances[0].y;
	while (anims != NULL)
	{
		anim = (t_anim *)anims->content;
		iterate_frames(anim->frames, x, y);
		anims = anims->next;
	}
}

void	sync_enemy(t_anim *current, int x, int y)
{
	t_list *frames;
	mlx_image_t *img;

	frames = current->frames;
	while (frames)
	{
		img = (mlx_image_t *)frames->content;
		img->instances[current->instance].x = x;
		img->instances[current->instance].y = y;
		frames = frames->next;
	}
}

void	sync_anim(t_enemy *enemy)
{
	int		x;
	int		y;

	x = enemy->base->instances[enemy->right->instance].x;
	y = enemy->base->instances[enemy->right->instance].y;
	sync_enemy(enemy->left, x, y);
	sync_enemy(enemy->right, x, y);

}

void	sync_char(t_game *game)
{
	mlx_image_t	*base;

	base = game->p->char_idle->frames->content;
	sync_anim_frames(base, game->p->char_anims);
	sync_anim_frames(base, game->g->char_anims);
}