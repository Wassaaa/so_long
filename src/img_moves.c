/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:54:18 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 22:57:55 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	image_right(void *image)
{
	mlx_image_t *img;

	img = (mlx_image_t *)image;
	img->instances[0].x += SPEED;
}

void	image_left(void *image)
{
	mlx_image_t *img;

	img = (mlx_image_t *)image;
	img->instances[0].x -= SPEED; 
}

void	image_down(void *image)
{
	mlx_image_t *img;

	img = (mlx_image_t *)image;
	img->instances[0].y += SPEED; 
}

void	image_up(void *image)
{
	mlx_image_t *img;

	img = (mlx_image_t *)image;
	img->instances[0].y -= SPEED; 
}