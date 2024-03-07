/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_alpha_blend.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:44:42 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:06:50 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static uint32_t	calculate_rgb_blend(t_rgba src, t_rgba dst)
{
	t_rgba	out;
	float	red;
	float	green;
	float	blue;
	float	out_a;

	out_a = src.a_norm + dst.a_norm * (1 - src.a_norm);
	if (out_a <= 0)
		return ((uint32_t)0);
	red = src.r * src.a_norm;
	green = src.g * src.a_norm;
	blue = src.b * src.a_norm;
	red += (dst.r * dst.a_norm * (1 - src.a_norm));
	green += (dst.g * dst.a_norm * (1 - src.a_norm));
	blue += (dst.b * dst.a_norm * (1 - src.a_norm));
	out.r = (uint8_t)(red / out_a);
	out.g = (uint8_t)(green / out_a);
	out.b = (uint8_t)(blue / out_a);
	out.a = (uint8_t)(out_a * 255);
	return ((out.r << 24) | (out.g << 16) | (out.b << 8) | out.a);
}

uint32_t	alpha_blend(t_rgba src_color, t_rgba dst_color)
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
