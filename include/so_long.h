/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/12 20:33:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <libft.h>
#include <MLX42/MLX42.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_anim
{
	t_list		*frames;
	int			frame_speed;
	double		accum;
	int			current_frame_num;
	int			mirrored;
	long int	updated_at;
	long int	frame_count;
}				t_anim;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*tile;
	mlx_image_t	*rock;
	mlx_image_t *item;
	t_anim		*char_idle;
	t_anim		*char_move;
	int			game_status;
	uint32_t	char_size;
	uint32_t	tile_size;
	uint32_t	item_size;
}				t_game;

typedef struct s_sprite
{
	char		*f_path;
	int			frame_count;
	int			frame_speed;
	uint32_t	size;
}			t_sprite;

t_list	*ft_lstget(t_list *l, int n);

#endif