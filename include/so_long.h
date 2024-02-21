/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:38:13 by aklein            #+#    #+#             */
/*   Updated: 2024/02/21 14:56:44 by aklein           ###   ########.fr       */
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

# define FREE 0
# define WALL 1
# define COLL 2
# define EXIT 3
# define PLAYER 5
# define ENEMY 4

# define UP 0
# define RIGHT 1
# define DOWN 2
# define LEFT 3

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
	int				frame_speed;
	double			accum;
	int				cur_f;
	long int		frame_count;
	bool			is_active;
	bool			full_cycle;
	int				type;
}					t_anim;

typedef struct s_map_element
{
	int				type;
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
	int				char_x;
	int				char_y;
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
	int				x;
	int				y;
	int				to;
	t_anim			*anim;
	t_anim			*anim_g;
	t_map_element	*el;
}					t_movement;

typedef struct s_enemy
{
	t_list			*enemy_anims;
	t_anim			*move_left;
	t_anim			*move_right;
	t_point			off;
	t_map_element	*el;
	int				index;
}					t_enemy;

typedef struct s_player
{
	t_list			*char_anims;
	t_map_element	*el;
	t_anim			*char_idle;
	t_anim			*char_idle_l;
	t_anim			*char_right;
	t_anim			*char_left;
	t_anim			*char_up;
	t_anim			*char_down;
	t_anim			*char_roll_right;
	t_anim			*char_roll_left;
	t_anim			*hair;
	t_anim			*head;
	t_point			off;
	char			last_move;
	t_map_element	*facing;
}					t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	t_map			*map;
	t_player		*backup;
	t_player		*p;
	t_enemy			*e;
	t_list			*enemies;
	t_player		*g;
	t_movement		*movement;
	t_list			*free_imgs;
	t_list			*wall_imgs;
	t_list			*coll_imgs;
	t_list			*exit_imgs;
	t_list			*prio;
	t_anim			*next;
	int				score;
	int				fps;
	int				game_status;
	int				move_speed;
	int				char_size;
	int				tile_size;
	int				coll_size;
	int				exit_size;
	int				ammo;
	int				last_ammo;
	int				random;
}					t_game;

typedef struct s_sprite
{
	char			*f_path;
	int				frame_count;
	int				frame_speed;
	int				mirrored;
}					t_sprite;

// init
void				init_player(t_game *game);
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

// img moves
void				image_right(t_game *game, void *image);
void				image_left(t_game *game, void *image);
void				image_up(t_game *game, void *image);
void				image_down(t_game *game, void *image);

// char moves
void				next_move(t_game *game);
int					move_allowed(t_map_element *el);
void				move_to(t_game *game, t_map_element *el, int to);
void				go_right(t_game *game);
void				go_left(t_game *game);
void				go_up(t_game *game);
void				go_down(t_game *game);

// animation
void				toggle_states(t_game *game, t_list *anims, t_anim *current);
void				roll_animations(t_game *game);
void				animation_loop(t_list *anims, double dt);
void				do_move(t_game *game);
void				do_idle(t_game *game);
void				finish_prio(t_game *game);

// frames sync
void				sync_anim_frames(mlx_image_t *base, t_list *anims);
void				sync_char(t_game *game);

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

#endif
