/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:05:38 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 04:01:09 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	draw_wall(t_game *game, t_map_element *el)
{
	mlx_image_t	*wall_bg;
	mlx_image_t	*wall_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	wall_bg = ft_lstget(game->free_imgs, FREE_C - 1)->content;
	wall_img = ft_lstget(game->wall_imgs, get_random()
			% ft_lstsize(el->images))->content;
	el->img = wall_img;
	if (el->type == WALL)
	{
		el->bg_instance = mlx_image_to_window(game->mlx, wall_bg, x, y);
		if (el->bg_instance == -1)
			error(EXIT_FAILURE, E_MLX);
		mlx_set_instance_depth(&wall_bg->instances[el->bg_instance], FREE);
	}
	el->instance = mlx_image_to_window(game->mlx, wall_img, x, y);
	if (el->instance == -1)
		error(EXIT_FAILURE, E_MLX);
	mlx_set_instance_depth(&wall_img->instances[el->instance], WALL);
}

void	draw_free(t_game *game, t_map_element *el)
{
	mlx_image_t	*free_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	free_img = ft_lstget(el->images, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, free_img, x, y);
	if (el->bg_instance == -1)
		error(EXIT_FAILURE, E_MLX);
	el->instance = 0;
	mlx_set_instance_depth(&free_img->instances[el->bg_instance], FREE);
}

void	draw_coll(t_game *game, t_map_element *el)
{
	mlx_image_t	*coll_bg;
	mlx_image_t	*coll_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	coll_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	coll_img = ft_lstget(game->coll_imgs, 0)->content;
	el->bg_instance = mlx_image_to_window(game->mlx, coll_bg, x, y);
	if (el->bg_instance == -1)
		error(EXIT_FAILURE, E_MLX);
	x += game->map->coll_off.x;
	y += game->map->coll_off.y;
	el->instance = mlx_image_to_window(game->mlx, coll_img, x, y);
	if (el->instance == -1)
		error(EXIT_FAILURE, E_MLX);
	el->img = coll_img;
	mlx_set_instance_depth(&coll_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&coll_img->instances[el->instance], game->z++);
}

void	draw_exit(t_game *game, t_map_element *el)
{
	mlx_image_t	*exit_bg;
	mlx_image_t	*exit_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	exit_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	exit_img = ft_lstget(game->exit_imgs, get_random()
			% ft_lstsize(el->images))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, exit_bg, x, y);
	if (el->bg_instance == -1)
		error(EXIT_FAILURE, E_MLX);
	el->instance = mlx_image_to_window(game->mlx, exit_img, x, y);
	if (el->instance == -1)
		error(EXIT_FAILURE, E_MLX);
	el->img = exit_img;
	mlx_set_instance_depth(&exit_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&exit_img->instances[el->instance], EXIT);
}
