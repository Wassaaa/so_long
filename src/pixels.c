/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:16:36 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 21:13:18 by aklein           ###   ########.fr       */
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

	start_location = img->pixels + (y * img->width + x) * BPP;
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

//
t_list	*get_recolor_list(void)
{
	t_recolor	*recolor;
	t_list		*recolors;

	recolors = NULL;
	recolor = ft_calloc(1, sizeof(t_recolor));
	recolor->remove = 0xEFEEEFFF;
	recolor->replace = 0x5C62E6FF;
	ft_lstadd_back(&recolors, ft_lstnew(recolor));
	recolor = ft_calloc(1, sizeof(t_recolor));
	recolor->remove = 0xA7A8A7FF;
	recolor->replace = 0x4045A0FF;
	ft_lstadd_back(&recolors, ft_lstnew(recolor));
	recolor = ft_calloc(1, sizeof(t_recolor));
	recolor->remove = 0x00FF00FF;
	recolor->replace = 0x00000000;
	ft_lstadd_back(&recolors, ft_lstnew(recolor));
	return (recolors);
}


uint32_t	check_recolor(uint32_t color)
{
	t_recolor	*recolor;
	t_list		*swaps;

	swaps = get_recolor_list();
	while (swaps)
	{
		recolor = (t_recolor *)swaps->content;
		if (color == recolor->remove)
			return (recolor->replace);
		swaps = swaps->next;
	}
	return (color);
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
			color = check_recolor(color);
			if (valid_pixel_spot(dst, x + i, y + j) && not_transparent(color))
				mlx_put_pixel(dst, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
