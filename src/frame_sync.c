/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:46:24 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 00:36:15 by aklein           ###   ########.fr       */
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

void	sync_char(t_game *game)
{
	mlx_image_t	*base;

	base = game->p->char_idle->frames->content;
	sync_anim_frames(base, game->p->char_anims);
	sync_anim_frames(base, game->g->char_anims);
}