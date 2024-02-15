/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/15 23:20:05 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 1024

# define CHAR_SIZE 512
# define TILE_SIZE 98
# define COLL_SIZE 80

# define WALL_C 3
# define EXIT_C 1
# define FREE_C 3
# define COLL_C 1

# define BPP sizeof(int32_t)
# define SPEED 5;

# define EMPTY 0
# define WALL 1
# define COLL 2
# define EXIT 3
# define PLAYER 4

typedef struct s_anim
{
	t_list		*frames;
	int			frame_speed;
	double		accum;
	int			cur_f;
	long int	frame_count;
	bool		is_active;
	bool		one_cycle;
	bool		going_up;
}				t_anim;

typedef struct s_map_element
{
	int			type;
	int			x;
	int			y;
	int			instance;
	int			img_count;
	t_anim		*anim;
	t_list		*images;
}				t_map_element;

typedef struct s_map
{
	t_list		*elements;
}				t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_list		*char_anims;
	t_list		*free_imgs;
	t_list		*wall_imgs;
	t_list		*coll_imgs;
	t_list		*exit_imgs;
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
	uint32_t	coll_size;
}				t_game;

typedef struct s_sprite
{
	char		*f_path;
	int			frame_count;
	int			frame_speed;
	int			mirrored;
}				t_sprite;

void			get_animations(t_game *game);
t_list			*ft_lstget(t_list *l, int n);
t_list			*safe_lstnew(void *content);

// pixels
int32_t			get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void			get_mirrored(mlx_image_t *dst, mlx_image_t *src);
void			img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);
void			color_from_src(mlx_image_t *dst, mlx_image_t *src);

// img moves
void			image_right(void *image);
void			image_left(void *image);
void			image_up(void *image);
void			image_down(void *image);

// char moves
void			move_right(t_game *game);
void			move_left(t_game *game);
void			move_up(t_game *game);
void			move_down(t_game *game);

void			sync_anim_frames(mlx_image_t *base, t_list *anims);

void			error(void);

void			read_map(t_game *game, char *map_file);

// new map stuff
void			fill_elements(t_game *game, char *line, int y);
void			load_map_textures(t_game *game);

#endif
