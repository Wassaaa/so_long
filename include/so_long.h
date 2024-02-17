/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/17 04:14:48 by aklein           ###   ########.fr       */
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
# define ROLL_CHANCE 15
# define CHAR_SIZE 384
# define CHAR_X_OFF -145
# define CHAR_Y_OFF -250
# define TILE_SIZE 98
# define COLL_SIZE 80

# define WALL_C 3
# define EXIT_C 1
# define FREE_C 2
# define COLL_C 1

# define SPEED 5

# define FREE 0
# define WALL 1
# define COLL 2
# define EXIT 3
# define PLAYER 4

# define UP 0
# define RIGHT 1
# define DOWN 2
# define LEFT 3

typedef struct s_anim
{
	t_list		*frames;
	int			frame_speed;
	double		accum;
	int			cur_f;
	long int	frame_count;
	bool		is_active;
}				t_anim;

typedef struct s_map_element
{
	int			type;
	int			x;
	int			y;
	int			instance;
	t_list		*images;
}				t_map_element;

typedef struct s_map
{
	t_list		*elements;
	int			char_x;
	int			char_y;
	int			width;
	int			height;
}				t_map;

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct s_movement
{
	int			active;
	int			x;
	int			y;
	int			to;
	t_anim		*anim;
}				t_movement;

typedef struct s_player
{
	t_list		*char_anims;
	t_anim		*char_idle;
	t_anim		*char_idle_l;
	t_anim		*char_right;
	t_anim		*char_left;
	t_anim		*char_up;
	t_anim		*char_down;
	t_anim		*char_roll_right;
	t_anim		*char_roll_left;
	t_anim		*hair;
	t_anim		*head;
	t_point		off;
	char		last_move;
}				t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	*p;
	t_movement	*movement;
	t_list		*free_imgs;
	t_list		*wall_imgs;
	t_list		*coll_imgs;
	t_list		*exit_imgs;
	int			game_status;
	int			move_speed;
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

// init
void			init_player(t_game *game);
t_game			*init_game(void);

// pixels
int32_t			get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void			get_mirrored(mlx_image_t *dst, mlx_image_t *src);
void			img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);
void			color_from_src(mlx_image_t *dst, mlx_image_t *src);

// img moves
void			image_right(t_game *game, void *image);
void			image_left(t_game *game, void *image);
void			image_up(t_game *game, void *image);
void			image_down(t_game *game, void *image);

// char moves
void			go_right(t_game *game);
void			go_left(t_game *game);
void			go_up(t_game *game);
void			go_down(t_game *game);

// animation
void			toggle_states(t_game *game, t_anim *current);
void			animation_loop(t_list *anims, double dt);

// frames sync
void			sync_anim_frames(mlx_image_t *base, t_list *anims);
void			sync_char(t_game *game);

// maps & textures
void			read_map(t_game *game, char *map_file);
void			fill_elements(t_game *game, char *line, int y);
void			load_map_textures(t_game *game);
void			get_animations(t_game *game);

// get moves
void			next_move(t_game *game);
void			error(void);

// helpers
t_list			*ft_lstget(t_list *l, int n);
t_list			*safe_lstnew(void *content);

#endif
