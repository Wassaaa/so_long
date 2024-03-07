/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:16:36 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:07:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*start;
	int32_t	color;

	if (!valid_px(img, x, y))
		return (0xFF000000);
	start = img->pixels + (y * img->width + x) * 4;
	color = get_rgba(*(start), *(start + 1), *(start + 2), *(start + 3));
	return (color);
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
			color = get_pixel_color(src, src->width - i - 1, j);
			if (valid_px(dst, i, j))
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
			if (valid_px(dst, i, j) && not_tp(dest_color))
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
	t_rgba		src_color;
	t_rgba		dst_color;
	uint32_t	blended_color;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			src_color.color = get_pixel_color(src, i, j);
			if (valid_px(dst, x + i, y + j) && not_tp(src_color.color))
			{
				dst_color.color = get_pixel_color(dst, x + i, y + j);
				blended_color = alpha_blend(src_color, dst_color);
				mlx_put_pixel(dst, x + i, y + j, blended_color);
			}
			j++;
		}
		i++;
	}
}
