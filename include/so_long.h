/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/27 04:35:29 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
# define ROLL_CHANCE 5
# define PLAYER_X_OFF -145
# define PLAYER_Y_OFF -250
# define COLL_X_OFF -60
# define COLL_Y_OFF -100
# define PLAYER_SIZE 384
# define TILE_SIZE 100
# define COLL_SIZE 200
# define EXIT_SIZE 120

# define WALL_C 3
# define EXIT_C 1
# define FREE_C 4
# define COLL_C 1

# define SPEED 500.0f
# define MIN_SPEED 50.0f

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

typedef enum s_anims
{
	A_UP,
	A_RIGHT,
	A_DOWN,
	A_LEFT,
	A_IDLE_R,
	A_IDLE_L,
	A_ROLL_R,
	A_ROLL_L,
	A_COUNT
}					t_anims;

typedef struct t_anims
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
	int				frame_count;
	bool			is_active;
	bool			full_cycle;
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
	mlx_instance_t	base;
	t_anim			*anims[A_COUNT];
	t_point			off;
	t_point			pos;
	t_map_element	*facing;
	int				index;
	t_movement		*movement;
	float			move_speed;
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
	float			scale;
	int				fd;
}					t_game;

typedef struct s_sprite
{
	char			*f_path;
	int				frame_count;
	int				frame_speed;
	int				mirrored;
}					t_sprite;

typedef void		(*t_img_move)(t_entity *, float);
typedef void		(*t_move)(t_game *game, t_entity *entity);

// init
t_game				**get_game(void);
t_game				*init_game(void);
void				start_mlx(t_game *game);
void				fix_sizes(t_game *game);
void				entity_speed(t_game *game);

// display
void				show_fps(t_game *game);
int					win_lose(t_game *game);

// pixels
int32_t				get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void				get_mirrored(mlx_image_t *d, mlx_image_t *s);
void				img_to_img(mlx_image_t *d, mlx_image_t *s, int x, int y);
void				color_from_src(mlx_image_t *d, mlx_image_t *s);

// draw stuff
void				draw_map(t_game *game);
void				draw_wall(t_game *game, t_map_element *el);
void				draw_free(t_game *game, t_map_element *el);
void				draw_coll(t_game *game, t_map_element *el);
void				draw_exit(t_game *game, t_map_element *el);
void				draw_enemy(t_game *game, t_map_element *el);
void				draw_player(t_game *game, t_map_element *el);
void				draw_gun_anim(t_game *game);
void				draw_anims(mlx_t *mlx, t_entity *ent, int x, int y);
void				build_anims(t_entity *base_entity, t_entity *ent);
void				fix_depth(t_entity *ent, int *z);

// moves
void				next_move(t_game *game);
void				do_idle(t_game *game);
int					move_allowed(t_map_element *el);

// entity moves
void				move_it(t_game *game, t_entity *entity, int to);
void				entity_move_to(t_game *game, t_entity *entity);
void				ent_up(t_game *game, t_entity *entity);
void				ent_right(t_game *game, t_entity *entity);
void				ent_down(t_game *game, t_entity *entity);
void				ent_left(t_game *game, t_entity *entity);

void				img_up(t_entity *entity, float dt);
void				img_right(t_entity *entity, float dt);
void				img_down(t_entity *entity, float dt);
void				img_left(t_entity *entity, float dt);

// animation
void				roll_animations(t_game *game);
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
void				image_toggle(t_entity *ent, bool onoff);
void				handle_shoot(t_game *game);

// helpers
t_list				*ft_lstget(t_list *l, int n);
t_list				*safe_lstnew(void *content);
void				*safe_ft_calloc(size_t count, size_t size);
void				error(void);
void				null_content(void *content);
void				clear_anim(t_anim **anim);
size_t				get_random(void);

#endif
