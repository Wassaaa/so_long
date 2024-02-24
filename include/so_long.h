/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/24 03:03:37 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
# define ROLL_CHANCE 5
# define CHAR_SIZE 384
# define CHAR_X_OFF -145
# define CHAR_Y_OFF -250
# define COLL_X_OFF -60
# define COLL_Y_OFF -100
# define TILE_SIZE 100
# define COLL_SIZE 200
# define EXIT_SIZE 120

# define WALL_C 3
# define EXIT_C 1
# define FREE_C 4
# define COLL_C 1

# define SPEED 7

typedef enum s_type
{
	FREE,
	WALL,
	EXIT,
	COLL,
	ENEMY,
	PLAYER
}					t_type;

typedef enum s_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
}					t_direction;

typedef struct s_rgba
{
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	float			a_norm;
}					t_rgba;

typedef struct s_anim
{
	t_list			*frames;
	int				instance;
	int				frame_speed;
	double			accum;
	int				cur_f;
	long int		frame_count;
	bool			is_active;
	bool			full_cycle;
	t_type			type;
}					t_anim;

typedef struct s_map_element
{
	t_type			type;
	int				x;
	int				y;
	int				instance;
	int				bg_instance;
	t_list			*images;
	mlx_image_t		*img;
}					t_map_element;

typedef struct s_map
{
	t_list			*elements;
	int				colls;
	int				coll_off_x;
	int				coll_off_y;
	int				width;
	int				height;
}					t_map;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct s_movement
{
	int				active;
	int				to;
	t_point			tar;
	t_anim			*anim;
	t_map_element	*el;
}					t_movement;

typedef struct s_entity
{
	t_list			*anims;
	mlx_instance_t	base;
	t_anim			*up;
	t_anim			*right;
	t_anim			*down;
	t_anim			*left;
	t_anim			*idle_r;
	t_anim			*idle_l;
	t_anim			*roll_r;
	t_anim			*roll_l;
	t_point			off;
	t_point			pos;
	t_map_element	*facing;
	int				index;
	t_movement		*movement;
	int				move_speed;
	t_anim			*current;
	t_anim			*next;
}					t_entity;

typedef struct s_game
{
	mlx_t			*mlx;
	t_map			*map;
	t_entity		*p;
	t_entity		*e;
	t_list			*enemies;
	t_entity		*g;
	t_list			*free_imgs;
	t_list			*wall_imgs;
	t_list			*coll_imgs;
	t_list			*exit_imgs;
	t_list			*prio;
	t_anim			*next;
	int				score;
	int				fps;
	int				game_status;
	int				char_size;
	int				tile_size;
	int				coll_size;
	int				exit_size;
	int				ammo;
	int				last_ammo;
	int				z;
}					t_game;

typedef struct s_sprite
{
	char			*f_path;
	int				frame_count;
	int				frame_speed;
	int				mirrored;
}					t_sprite;

typedef void		(*t_img_move)(t_entity *);
typedef void		(*t_move)(t_game *game, t_entity *entity);

// init
t_game				*init_game(void);
void				start_mlx(t_game *game);
void				fix_sizes(t_game *game);

// display
void				show_fps(t_game *game);
int					win_lose(t_game *game);

// pixels
int32_t				get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void				get_mirrored(mlx_image_t *dst, mlx_image_t *src);
void				img_to_img(mlx_image_t *dst, mlx_image_t *src, int x,
						int y);
void				color_from_src(mlx_image_t *dst, mlx_image_t *src);

// draw stuff
void				draw_map(t_game *game);

// char moves
void				next_move(t_game *game);
int					move_allowed(t_map_element *el);

// enemy moves
void				move_it(t_game *game, t_entity *entity, int to);
void				entity_move_to(t_game *game, t_entity *entity);
void				entity_up(t_game *game, t_entity *entity);
void				entity_right(t_game *game, t_entity *entity);
void				entity_down(t_game *game, t_entity *entity);
void				entity_left(t_game *game, t_entity *entity);

void				img_up(t_entity *entity);
void				img_right(t_entity *entity);
void				img_down(t_entity *entity);
void				img_left(t_entity *entity);

// animation
void				roll_animations(t_game *game);
void				do_idle(t_game *game);

// frames sync
void				sync_anim(t_entity *enemy);

// maps & textures
void				read_map(t_game *game, char *map_file);
void				fill_elements(t_game *game, char *line, int y);
void				load_map_textures(t_game *game);
void				get_animations(t_game *game);

// game elements
void				got_gun(t_game *game);
void				gun_picked_up(t_game *game);
void				item_collection(t_game *game);
void				image_toggle(t_list *anims, bool onoff);
void				handle_shoot(t_game *game);

// helpers
t_list				*ft_lstget(t_list *l, int n);
t_list				*safe_lstnew(void *content);
void				error(void);
void				null_content(void *content);
void				clear_anim(t_anim **anim);
size_t				get_random(void);

#endif
