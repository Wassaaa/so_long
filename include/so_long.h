/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 19:50:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <libft.h>
#include <MLX42/MLX42.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BPP sizeof(int32_t)

typedef struct s_anim
{
	t_list		*frames;
	int			frame_speed;
	double		accum;
	int			cur_f;
	long int	frame_count;
	bool		is_active;
	bool		one_cycle;
}				t_anim;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*tile;
	mlx_image_t	*rock;
	mlx_image_t *item;
	t_anim		*char_idle;
	t_anim		*char_right;
	t_anim		*char_left;
	t_anim		*char_up;
	t_anim		*char_down;
	t_anim		*char_roll_right;
	t_anim		*char_roll_left;
	t_anim		*hair;
	t_anim		*head;
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
	int			mirrored;			
}				t_sprite;

typedef struct s_recolor
{
	uint32_t	remove;
	uint32_t	replace;
}				t_recolor;

void	get_animations(t_game *game);
t_list	*ft_lstget(t_list *l, int n);

//pixels
int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void	get_mirrored(mlx_image_t *dst, mlx_image_t *src);
void	img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

//img moves
void	image_right(void *image);
void	image_left(void *image);
void	image_up(void *image);
void	image_down(void *image);

//char moves
void	move_right(t_game *game);
void	move_left(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);

void	sync_char_frames(t_game *game);

void error(void);

#endif