/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:16:36 by aklein            #+#    #+#             */
/*   Updated: 2024/02/18 22:25:52 by aklein           ###   ########.fr       */
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
uint32_t	alpha_blend(uint32_t src_color, uint32_t dst_color)
{
	uint8_t		src_alpha;
	uint8_t		src_red;
	uint8_t		src_green;
	uint8_t		src_blue;
	uint8_t		dst_red;
	uint8_t		dst_green;
	uint8_t		dst_blue;
	float		alpha;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;

	src_red = (src_color >> 24) & 0xFF;
	src_green = (src_color >> 16) & 0xFF;
	src_blue = (src_color >> 8) & 0xFF;
	src_alpha = (src_color) & 0xFF;
	dst_red = (dst_color >> 24) & 0xFF;
	dst_green = (dst_color >> 16) & 0xFF;
	dst_blue = (dst_color >> 8) & 0xFF;
	alpha = src_alpha / 255.0f;
	red = (uint8_t)(alpha * src_red + (1 - alpha) * dst_red);
	green = (uint8_t)(alpha * src_green + (1 - alpha) * dst_green);
	blue = (uint8_t)(alpha * src_blue + (1 - alpha) * dst_blue);
	return (red << 24) | (green << 16) | (blue << 8) | src_alpha;
}


void	img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	src_color;
	uint32_t	dst_color;
	uint32_t	blended_color;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			src_color = get_pixel_color(src, i, j);
			if (valid_pixel_spot(dst, x + i, y + j) && not_transparent(src_color))
			{
				dst_color = get_pixel_color(dst, x + i, y + j);
				blended_color = alpha_blend(src_color, dst_color);
				mlx_put_pixel(dst, x + i, y + j, blended_color);
			}
			j++;
		}
		i++;
	}
}
