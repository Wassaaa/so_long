/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:02:41 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 05:59:19 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include <so_long.h>

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
	E_MAP_BER,
	E_MAP_ROUTE,
	E_MAP_WALL,
	E_MAP_RECT,
	E_MAP_EL,
	E_MAP_PLAYERS,
	E_MAP_COLLS,
	E_MAP_EXITS,
	E_MAP_SIZE,
	E_MAP_SIZE_TILE,
	E_MAP_SIZE_BIG,
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

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_map
{
	t_list			*elements;
	int				colls;
	int				players;
	int				exits;
	t_point			coll_off;
	int				width;
	int				height;
}					t_map;

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
	t_map_element	*current_el;
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
	int				rocks;
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

#endif