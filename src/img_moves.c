/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:54:18 by aklein            #+#    #+#             */
/*   Updated: 2024/02/16 21:11:35 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	image_right(t_game *game, void *image)
{
	mlx_image_t *img;
	int			x;

	img = (mlx_image_t *)image;
	x = img->instances[0].x;
	if ((game->movement->x - x) > SPEED)
		x = SPEED;
	else
	{
		x = game->movement->x - x;
		ft_bzero(game->movement, sizeof(t_movement));
	}
	img->instances[0].x += x;
}

void	image_left(t_game *game, void *image)
{
	mlx_image_t *img;
	int			x;

	img = (mlx_image_t *)image;
	x = img->instances[0].x;
	if ((x - game->movement->x) > SPEED)
		x = SPEED;
	else
		x = x - game->movement->x;
	img->instances[0].x -= x;
}

void	image_down(t_game *game, void *image)
{
	mlx_image_t *img;
	int			y;

	img = (mlx_image_t *)image;
	y = img->instances[0].y;
	if (game->movement->y - y > SPEED)
		y = SPEED;
	else
		y = game->movement->y - y;
	img->instances[0].y += y;
}

void	image_up(t_game *game, void *image)
{
	mlx_image_t *img;
	int			y;

	img = (mlx_image_t *)image;
	y = img->instances[0].y;
	if (y - game->movement->y > SPEED)
		y = SPEED;
	else
		y = y - game->movement->y;
	img->instances[0].y -= y;
}
