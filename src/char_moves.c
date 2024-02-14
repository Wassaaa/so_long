/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:55:46 by aklein            #+#    #+#             */
/*   Updated: 2024/02/14 17:53:13 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	move_right(t_game *game)
{
	mlx_image_t	*img;

	img = game->char_idle->frames->content;
	image_right(img);
	sync_anim_frames(img, game->char_anims);
}

void	move_left(t_game *game)
{
	mlx_image_t	*img;

	img = game->char_idle->frames->content;
	image_left(img);
	sync_anim_frames(img, game->char_anims);
}

void	move_up(t_game *game)
{
	mlx_image_t	*img;

	img = game->char_idle->frames->content;
	image_up(img);
	sync_anim_frames(img, game->char_anims);
}

void	move_down(t_game *game)
{
	mlx_image_t	*img;

	img = game->char_idle->frames->content;
	image_down(img);
	sync_anim_frames(img, game->char_anims);
}