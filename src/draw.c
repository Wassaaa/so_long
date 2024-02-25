/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:07:53 by aklein            #+#    #+#             */
/*   Updated: 2024/02/24 19:27:09 by aklein           ###   ########.fr       */
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
	wall_img = ft_lstget(game->wall_imgs, get_random() % ft_lstsize(el->images))->content;
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

	free_img = ft_lstget(el->images, get_random() % (FREE_C - 1))->content;
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

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	coll_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	coll_img = ft_lstget(game->coll_imgs, 0)->content;
	el->bg_instance = mlx_image_to_window(game->mlx, coll_bg, x, y);
	x += game->map->coll_off_x;
	y += game->map->coll_off_y;
	el->instance = mlx_image_to_window(game->mlx, coll_img, x, y);
	el->img = coll_img;
	game->map->colls++;
	mlx_set_instance_depth(&coll_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&coll_img->instances[el->instance], game->z++);
}

void	draw_exit(t_game *game, t_map_element *el)
{
	mlx_image_t	*exit_bg;
	mlx_image_t	*exit_img;
	int			x;
	int			y;

	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	exit_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	exit_img = ft_lstget(game->exit_imgs, get_random() % ft_lstsize(el->images))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, exit_bg, x, y);
	el->instance = mlx_image_to_window(game->mlx, exit_img, x, y);
	el->img = exit_img;
	mlx_set_instance_depth(&exit_bg->instances[el->bg_instance], FREE);
	mlx_set_instance_depth(&exit_img->instances[el->instance], EXIT);
}

void	frames_to_window(mlx_t *mlx, t_list *anims, int x, int y)
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
}

void	fix_depth(t_list *anims, int *z)
{
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
			mlx_set_instance_depth(&frame->instances[anim->instance], *z);
			temp = temp->next;
		}
		anims = anims->next;
		*z = *z + 2;
	}
}

t_entity	*build_enemy(t_game *game)
{
	t_entity *enemy;

	enemy = ft_calloc(1, sizeof(t_entity));
	if (!enemy)
		error();
	*enemy = *game->e;
	enemy->movement = ft_calloc(1, sizeof(t_movement));
	if (!enemy->movement)
		error();
	enemy->right = ft_calloc(1, sizeof (t_anim));
	enemy->left = ft_calloc(1, sizeof(t_anim));
	if (!enemy->right || !enemy->left)
		error();
	*enemy->right = *game->e->right;
	*enemy->left = *game->e->left;
	enemy->up = enemy->left;
	enemy->down = enemy->right;
	enemy->right->cur_f = get_random() % (enemy->right->frame_count - 1);
	enemy->left->cur_f = get_random() % (enemy->left->frame_count - 1);
	enemy->current = enemy->right;
	ft_lstadd_back(&game->e->anims, safe_lstnew(enemy->right));
	ft_lstadd_back(&game->e->anims, safe_lstnew(enemy->left));
	return (enemy);
}

int	draw_anim(mlx_t *mlx, t_anim *anim, int x, int y)
{
	mlx_image_t	*img;
	t_list		*frames;
	int			instance;

	frames = anim->frames;
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
	mlx_image_t	*base;
	t_entity		*enemy;
	int			x;
	int			y;
	static int	index = 0;

	enemy = build_enemy(game);
	enemy->pos.x = el->x;
	enemy->pos.y = el->y;
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	enemy_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, enemy_bg, x, y);
	mlx_set_instance_depth(&enemy_bg->instances[el->bg_instance], FREE);
	x += enemy->off.x;
	y += enemy->off.y;
	enemy->left->instance = draw_anim(game->mlx, enemy->left, x, y);
	enemy->right->instance = draw_anim(game->mlx, enemy->right, x, y);
	base = (mlx_image_t *)(enemy->right->frames->content);
	enemy->base = base->instances[enemy->right->instance];
	enemy->index = index++;
	ft_lstadd_back(&game->enemies, safe_lstnew(enemy));
}

void	draw_player(t_game *game, t_map_element *el)
{
	mlx_image_t *player_bg;
	t_list		*player_anims;
	mlx_image_t	*base;
	int			x;
	int			y;

	game->p->current = game->p->idle_r;
	game->p->pos.x = el->x;
	game->p->pos.y = el->y;
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	player_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, player_bg, x, y);
	mlx_set_instance_depth(&player_bg->instances[el->bg_instance], FREE);
	player_anims = game->p->anims;
	x += game->p->off.x;
	y += game->p->off.y;
	frames_to_window(game->mlx, player_anims, x, y);
	base = (mlx_image_t *)(game->p->right->frames->content);
	game->p->base = base->instances[game->p->right->instance];
}
void	draw_gun_anim(t_game *game)
{
	int				x;
	int				y;
	t_list			*temp;
	mlx_instance_t	instance;
	mlx_instance_t	p_instance;
	mlx_image_t		*img;
	mlx_image_t		*p_img;

	game->g->current = game->g->idle_r;
	x = game->p->pos.x;
	y = game->p->pos.y;
	frames_to_window(game->mlx, game->g->anims, x, y);
	fix_depth(game->g->anims, &game->z);
	temp = game->g->up->frames;
	while (temp)
	{
		img = (mlx_image_t *)temp->content;
		instance = img->instances[game->g->up->instance];
		p_img = (mlx_image_t *)game->p->up->frames->content;
		p_instance = p_img->instances[game->p->up->instance];
		mlx_set_instance_depth(&instance, p_instance.z - 1);
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
	fix_depth(game->e->anims, &game->z);
	fix_depth(game->p->anims, &game->z);
	draw_gun_anim(game);
}
