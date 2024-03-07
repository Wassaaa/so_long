/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:37:17 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define BPP sizeof(int32_t)

# define WIDTH 1920
# define HEIGHT 900
# define ROLL_CHANCE 5
# define PLAYER_X_OFF -145
# define PLAYER_Y_OFF -250
# define COLL_X_OFF -60
# define COLL_Y_OFF -100
# define PLAYER_SIZE 384
# define TILE_SIZE 100
# define COLL_SIZE 200
# define EXIT_SIZE 120
# define UI_W 257
# define UI_H 103

# define WALL_C 3
# define EXIT_C 1
# define FREE_C 4
# define COLL_C 1

# define SPEED 500.0f
# define MIN_SPEED 2.0f
# define ENEMY_MOD 0.5f
# define GOD_MODE 0

typedef enum e_ui_nbs
{
	UNITS,
	TENS,
	HUND,
	THOU,
	T_THOU,
	H_THOU,
	MIL,
	T_MIL,
	H_MIL,
	BIL,
	UI_MAX
}					t_ui_nbs;

typedef enum e_err
{
	E_MLX,
	E_MALLOC,
	E_MAP,
	E_MAP_ROUTE,
	E_MAP_WALL,
	E_MAP_RECT,
	E_MAP_EL,
	E_MAP_PLAYERS,
	E_MAP_COLLS,
	E_MAP_EXITS,
	E_MAP_SIZE,
	E_MAX

}					t_err;

typedef enum e_type
{
	FREE,
	WALL,
	EXIT,
	COLL,
	ENEMY,
	PLAYER
}					t_type;

typedef enum e_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
}					t_direction;

typedef enum e_anims
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
	int				frame_count;
	bool			is_active;
	bool			full_cycle;
}					t_anim;

typedef struct s_map_element
{
	int				type;
	int				x;
	int				y;
	int				visited;
	int				instance;
	int				bg_instance;
	t_list			*images;
	mlx_image_t		*img;
}					t_map_element;

typedef struct s_map
{
	t_list			*elements;
	int				colls;
	int				players;
	int				exits;
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
}					t_movement;

typedef struct s_entity
{
	mlx_instance_t	base;
	t_anim			*anims[A_COUNT];
	t_point			off;
	t_point			pos;
	t_map_element	*facing;
	t_movement		*movement;
	float			move_speed;
	float			move_step;
	t_anim			*current;
	t_anim			*next;
}					t_entity;

typedef struct s_ui
{
	mlx_image_t		*moves;
	t_point			moves_loc;
	mlx_image_t		*bg;
	int				moves_y;
	int				info_x;
	int				info_y;
	int				w;
	int				h;
	float			sc;
	mlx_image_t		*numbers[10];
	int				nb_parts[UI_MAX];
}					t_ui;

typedef struct s_game
{
	mlx_t			*mlx;
	t_ui			*ui;
	t_map			*map;
	t_entity		*p;
	t_entity		*e;
	t_list			*enemies;
	t_entity		*g;
	t_list			*free_imgs;
	t_list			*wall_imgs;
	t_list			*coll_imgs;
	t_list			*exit_imgs;
	unsigned int	moves;
	int				last_moves;
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
void				game_ui(t_game *game);
void				fix_ui_sizes(t_game *game);
void				generate_number_imgs(t_game *game);
void				display_number(t_game *game, unsigned int nb, t_point loc);
void				show_fps(t_game *game);
int					win_lose(t_game *game);
void				add_move(t_game *game);

// pixels
int					not_tp(uint32_t color);
int					valid_px(mlx_image_t *img, uint32_t x, uint32_t y);
int32_t				get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t			alpha_blend(t_rgba src_color, t_rgba dst_color);
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

// entity moves
void				move_enemy(t_game *game);
void				move_player(t_game *game);
void				move_image(t_entity *entity, float dt);
void				ent_up(t_game *game, t_entity *entity);
void				ent_right(t_game *game, t_entity *entity);
void				ent_down(t_game *game, t_entity *entity);
void				ent_left(t_game *game, t_entity *entity);
int					move_allowed(t_map_element *el);
void				add_move(t_game *game);

// animation
void				roll_animations(t_game *game);
void				anim_off(t_anim *anim);
void				movement_animation(t_entity *entity);
void				sync_anim(t_entity *enemy);

// map
void				map_info(t_game *game, char *map_file);
void				read_map(t_game *game, char *map_file);
void				map_valdiation(t_game *game, char *map_file);

// textures
void				load_map_textures(t_game *game);
void				get_animations(t_game *game);
t_anim				*load_animation(t_game *game, t_sprite sprite);
void				load_tiles(t_game *game, t_list **lst, char *pth, int len);
t_sprite			new_sprite(char *path, int f_cnt, int f_spd, int mir);
void				anim_to_anim(t_list *dest, t_list *src);
void				color_anim(t_list *dest, t_list *src);

// game elements
void				got_gun(t_game *game);
void				item_collection(t_game *game);
void				handle_shoot(t_game *game);

// helpers
t_list				*ft_lstget(t_list *l, int n);
t_list				*safe_lstnew(void *content);
void				*safe_ft_calloc(size_t count, size_t size);
size_t				get_random(void);

// error
void				error(int ret, int msg);
void				err_msg(int ret, int msg);
void				free_content(void *content);
void				clear_anim(t_anim **anim);

#endif
