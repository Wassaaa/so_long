/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:16:36 by aklein            #+#    #+#             */
/*   Updated: 2024/02/19 01:56:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int valid_px(mlx_image_t* img, uint32_t x, uint32_t y) {
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

int	not_tp(uint32_t color)
{
	uint8_t	alpha;

	alpha = (color) & 0xFF;
	if (alpha == 0)
		return (0);
	return (1);
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

uint32_t	calculate_rgb_blend(t_rgba src, t_rgba dst)
{
	float	red;
	float	green;
	float	blue;
	uint8_t out_alpha;
	float	out_a;
	uint8_t	r_out;
	uint8_t	g_out;
	uint8_t	b_out;
	

	out_a = src.a_norm + dst.a_norm * (1 - src.a_norm);
	if (out_a <= 0)
		return ((uint32_t)0);
	red = src.r * src.a_norm;
	green = src.g * src.a_norm;
	blue = src.b * src.a_norm;
	red += (dst.r * dst.a_norm * (1 - src.a_norm));
	green += (dst.g * dst.a_norm * (1 - src.a_norm));
	blue += (dst.b * dst.a_norm * (1 - src.a_norm));
	r_out = (uint8_t)(red / out_a);
	g_out = (uint8_t)(green  / out_a);
	b_out = (uint8_t)(blue / out_a);
	out_alpha = (uint8_t)(out_a * 255);
	return ((r_out << 24) | (g_out << 16) | (b_out << 8) | out_alpha);
}		

uint32_t alpha_blend(t_rgba src_color, t_rgba dst_color)
{
	src_color.r = (src_color.color >> 24) & 0xFF;
	src_color.g = (src_color.color >> 16) & 0xFF;
	src_color.b = (src_color.color >> 8) & 0xFF;
	src_color.a = src_color.color & 0xFF;
	dst_color.r = (dst_color.color >> 24) & 0xFF;
	dst_color.g = (dst_color.color >> 16) & 0xFF;
	dst_color.b = (dst_color.color >> 8) & 0xFF;
	dst_color.a = dst_color.color & 0xFF;

	src_color.a_norm = src_color.a / 255.0f;
	dst_color.a_norm = dst_color.a / 255.0f;

	return (calculate_rgb_blend(src_color, dst_color));
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
