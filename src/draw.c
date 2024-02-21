/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:07:53 by aklein            #+#    #+#             */
/*   Updated: 2024/02/21 21:01:17 by aklein           ###   ########.fr       */
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
	wall_img = ft_lstget(game->wall_imgs, rand() % ft_lstsize(el->images))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, wall_bg, x, y);
	el->instance = mlx_image_to_window(game->mlx, wall_img, x, y);
	el->img = wall_img;
	mlx_set_instance_depth(&wall_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&wall_img->instances[el->instance], WALL);
}

void	draw_free(t_game *game, t_map_element *el)
{
	mlx_image_t	*free_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;

	free_img = ft_lstget(el->images, rand() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, free_img, x, y);
	el->instance = 0;
	mlx_set_instance_depth(&free_img->instances[el->bg_instance], FREE);
}

void	draw_coll(t_game *game, t_map_element *el)
{
	mlx_image_t	*coll_bg;
	mlx_image_t	*coll_img;
	int			x;
	int			y;
	static int	i = 100;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	coll_bg = ft_lstget(game->free_imgs, rand() % (FREE_C - 1))->content;
	coll_img = ft_lstget(game->coll_imgs, 0)->content;
	el->bg_instance = mlx_image_to_window(game->mlx, coll_bg, x, y);
	x += game->map->coll_off_x;
	y += game->map->coll_off_y;
	el->instance = mlx_image_to_window(game->mlx, coll_img, x, y);
	el->img = coll_img;
	game->map->colls++;
	mlx_set_instance_depth(&coll_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&coll_img->instances[el->instance], i + COLL);
	i++;

}

void	draw_exit(t_game *game, t_map_element *el)
{
	mlx_image_t	*exit_bg;
	mlx_image_t	*exit_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	exit_bg = ft_lstget(game->free_imgs, rand() % (FREE_C - 1))->content;
	exit_img = ft_lstget(game->exit_imgs, rand() % ft_lstsize(el->images))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, exit_bg, x, y);
	el->instance = mlx_image_to_window(game->mlx, exit_img, x, y);
	el->img = exit_img;
	mlx_set_instance_depth(&exit_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&exit_img->instances[el->instance], EXIT);
}

int	frames_to_window(mlx_t *mlx, t_list *anims, int x, int y)
{
	mlx_image_t	*frame;
	t_anim		*anim;
	int			instance;
	t_list		*frames;

	instance = -1;
	while (anims != NULL)
	{
		anim = (t_anim *)anims->content;
		frames = anim->frames;
		while (frames)
		{
			frame = (mlx_image_t *)frames->content;
			instance = mlx_image_to_window(mlx, frame, x, y);
			anim->instance = instance;
			frame->instances[instance].enabled = false;
			frames = frames->next;
		}
		anims = anims->next;
	}
	if (instance == -1)
		error();
	return (instance);
}

void	fix_depth(t_list *anims)
{
	static int	i = 6;
	mlx_image_t	*frame;
	t_anim		*anim;
	t_list		*temp;

	while (anims != NULL)
	{
		anim = (t_anim *)anims->content;
		temp = anim->frames;
		while (temp)
		{
			frame = (mlx_image_t *)temp->content;
			mlx_set_instance_depth(&frame->instances[anim->instance], i);
			temp = temp->next;
		}
		anims = anims->next;
	}
	i = i + 2;
}

t_enemy	*build_enemy(t_game *game)
{
	t_enemy *enemy;

	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		error();
	*enemy = *game->e;
	enemy->move_left = ft_calloc(1, sizeof(t_anim));
	enemy->move_right = ft_calloc(1, sizeof (t_anim));
	if (!enemy->move_right || !enemy->move_left)
		error();
	*enemy->move_left = *game->e->move_left;
	*enemy->move_right = *game->e->move_right;
	enemy->move_right->cur_f = rand() % (enemy->move_right->frame_count - 1);
	enemy->move_left->cur_f = rand() % (enemy->move_left->frame_count - 1);
	enemy->current = enemy->move_right;
	ft_lstadd_back(&game->e->enemy_anims, safe_lstnew(enemy->move_left));
	ft_lstadd_back(&game->e->enemy_anims, safe_lstnew(enemy->move_right));
	return (enemy);
}

int	draw_anim(mlx_t *mlx, t_anim **anim, int x, int y)
{
	mlx_image_t	*img;
	t_list		*frames;
	int			instance;
	t_anim		*this_anim;

	this_anim = *anim;
	frames = this_anim->frames;
	instance = -1;
	while (frames)
	{
		img = (mlx_image_t *)frames->content;
		instance = mlx_image_to_window(mlx, img, x, y);
		img->instances[instance].enabled = false;
		frames = frames->next;
	}
	if (instance == -1)
		error();
	return (instance);
}

void	draw_enemy(t_game *game, t_map_element *el)
{
	mlx_image_t *enemy_bg;
	t_enemy		*enemy;
	int			x;
	int			y;
	static int	index = 0;

	enemy = build_enemy(game);
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	enemy_bg = ft_lstget(game->free_imgs, rand() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, enemy_bg, x, y);
	mlx_set_instance_depth(&enemy_bg->instances[el->bg_instance], FREE);
	x += enemy->off.x;
	y += enemy->off.y;
	enemy->move_left->instance = draw_anim(game->mlx, &enemy->move_left, x, y);
	enemy->move_right->instance = draw_anim(game->mlx, &enemy->move_right, x, y);
	enemy->el = el;
	enemy->index = index++;
	ft_lstadd_back(&game->enemies, safe_lstnew(enemy));
	// el->img = (mlx_image_t *)ft_lstget(game->e->move_right, 0)->content;
}

void	draw_player(t_game *game, t_map_element *el)
{
	mlx_image_t *player_bg;
	t_list		*player_anims;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	player_bg = ft_lstget(game->free_imgs, rand() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, player_bg, x, y);
	player_anims = game->p->char_anims;
	x += game->p->off.x;
	y += game->p->off.y;
	el->instance = frames_to_window(game->mlx, player_anims, x, y);
	mlx_set_instance_depth(&player_bg->instances[el->bg_instance], FREE);
	game->p->el = el;
}
void	draw_gun_anim(t_game *game)
{
	int				x;
	int				y;
	t_list			*temp;
	mlx_image_t		*img;
	int				char_z;

	temp = game->g->char_up->frames;
	x = game->p->el->x;
	y = game->p->el->y;
	game->g->el->instance = frames_to_window(game->mlx, game->g->char_anims, x, y);
	fix_depth(game->g->char_anims);
	while (temp)
	{
		img = (mlx_image_t *)temp->content;
		char_z = ((mlx_image_t *)(game->p->char_idle->frames->content))->instances[0].z;
		mlx_set_instance_depth(&img->instances[game->g->el->instance], char_z - 1);
		temp = temp->next;
	}

}

void	draw_map(t_game *game)
{
	t_map_element	*el;
	t_list			*tile;

	tile = game->map->elements;
	while (tile)
	{
		el = (t_map_element *)tile->content;
		if (el->type == WALL)
			draw_wall(game, el);
		if (el->type == FREE)
			draw_free(game, el);
		if (el->type == PLAYER)
			draw_player(game, el);
		if (el->type == ENEMY)
			draw_enemy(game, el);
		if (el->type == COLL)
			draw_coll(game, el);
		if (el->type == EXIT)
			draw_exit(game, el);
		tile = tile->next;
	}
	fix_depth(game->e->enemy_anims);
	fix_depth(game->p->char_anims);
	draw_gun_anim(game);
}
