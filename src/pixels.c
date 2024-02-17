/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:16:36 by aklein            #+#    #+#             */
/*   Updated: 2024/02/17 04:07:59 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int valid_pixel_spot(mlx_image_t* img, uint32_t x, uint32_t y) {
    return (x < img->width && y < img->height);
}

static int	get_rgba(int r, int g, int b, int a)
{
	int32_t	color;

	color = r << 24 | g << 16 | b << 8 | a;
	return (color);
}

int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y)
{
	if (x > img->width || y > img->height)
		return (0xFF000000);
	uint8_t	*start_location;
	uint8_t *red;
	uint8_t *green;
	uint8_t *blue;
	uint8_t *alpha;
	int		color;

	start_location = img->pixels + (y * img->width + x) * 4;
	red = start_location;
	green = start_location + 1;
	blue = start_location + 2;
	alpha = start_location + 3;
	color = get_rgba(*red, *green, *blue, *alpha);
	return (color);
}

int	not_transparent(uint32_t color)
{
	return (color != 0x00000000);
}

void	get_mirrored(mlx_image_t *dst, mlx_image_t *src)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			color = get_pixel_color(src, src->width - i, j);
			if (valid_pixel_spot(dst, i, j))
				mlx_put_pixel(dst, i, j, color);
			j++;
		}
		i++;
	}
}

void	color_from_src(mlx_image_t *dst, mlx_image_t *src)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color;
	uint32_t	dest_color;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			color = get_pixel_color(src, i, j);
			dest_color = get_pixel_color(dst, i, j);
			if (valid_pixel_spot(dst, i, j) && not_transparent(dest_color))
				mlx_put_pixel(dst, i, j, color);
			j++;
		}
		i++;
	}
}

void	img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			color = get_pixel_color(src, i, j);
			if (valid_pixel_spot(dst, x + i, y + j) && not_transparent(color))
				mlx_put_pixel(dst, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
