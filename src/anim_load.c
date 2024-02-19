/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:43:05 by aklein            #+#    #+#             */
/*   Updated: 2024/02/19 22:52:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_sprite	new_sprite(char *path, int f_cnt, int f_spd, int mirrored)
{
	t_sprite	sprite;

	sprite.f_path = path;
	sprite.frame_count = f_cnt;
	sprite.frame_speed = f_spd;
	sprite.mirrored = mirrored;
	return (sprite);
}

char *build_path(int i, char *path)
{
	char	*nr;
	char	*path_start;
	char	*full_path;

	nr = ft_itoa(i);
	path_start = ft_strjoin(path, nr);
	if (!path_start)
		error();
	full_path = ft_strjoin(path_start, ".png");
	if (!full_path)
		error();
	free(path_start);
	free(nr);
	return (full_path);
}

mlx_image_t	*get_img(t_game *game, char *path, int i, int mirr)
{
	char			*full_path;
	mlx_texture_t	*texture;
	mlx_image_t		*new_img;
	mlx_image_t		*mirrored;

	full_path = build_path(i, path);
	texture = mlx_load_png(full_path);
	if (!texture)
		error();
	new_img = mlx_texture_to_image(game->mlx, texture);
	if (!new_img)
		error();
	if (!mlx_resize_image(new_img, game->char_size, game->char_size))
		error();
	mlx_delete_texture(texture);
	free(full_path);
	if (mirr)
	{
		mirrored = mlx_new_image(game->mlx, new_img->width, new_img->height);
		get_mirrored(mirrored, new_img);
		mlx_delete_image(game->mlx, new_img);
		return (mirrored);
	}
	return (new_img);
}

t_anim	*load_animation(t_game *game, t_sprite sprite, t_list **anim_base, int list)
{
	t_anim			*anim;
	int				i;
	mlx_image_t		*new_img;

	anim = ft_calloc(1, sizeof(t_anim));
	if (!anim)
		error();
	anim->frame_speed = sprite.frame_speed;
	anim->frame_count = sprite.frame_count;
	i = 0;
	while (i < sprite.frame_count)
	{
		new_img = get_img(game, sprite.f_path, i++, sprite.mirrored);
		ft_lstadd_back(&anim->frames, safe_lstnew(new_img));
	}
	if (list)
		ft_lstadd_back(anim_base, safe_lstnew(anim));
	return (anim);
}

void	add_to_anim_frames(t_list *dest, t_list *src)
{
	mlx_image_t	*destination;
	mlx_image_t	*source;

	if (ft_lstsize(dest) != ft_lstsize(src))
		return ;
	while (dest)
	{
		destination = (mlx_image_t *)dest->content;
		source = (mlx_image_t *)src->content;
		img_to_img(destination, source, 0, 0);
		dest = dest->next;
		src = src->next;
	}
}

void	color_anim(t_list *dest, t_list *src)
{
	mlx_image_t	*destination;
	mlx_image_t	*source;

	if (ft_lstsize(dest) != ft_lstsize(src))
		return ;
	while (dest)
	{
		destination = (mlx_image_t *)dest->content;
		source = (mlx_image_t *)src->content;
		color_from_src(destination, source);
		dest = dest->next;
		src = src->next;
	}

}



void	set_types(t_list *anims, int type)
{
	t_anim	*anim;

	while (anims)
	{
		anim = (t_anim *)anims->content;
		anim->type = type;
		anims = anims->next;
	}
}


void	gun_picked_up(t_game *game)
{
	game->map->colls--;
	game->p->has_gun = true;
}

void	load_enemy (t_game *game)
{
	t_sprite enemy_fly;

	enemy_fly = new_sprite("./textures/enemy/fly_", 6, 100, 0);
	game->e->move_right = load_animation(game, enemy_fly, &game->e->enemy_anims, 1);
	enemy_fly.mirrored = 1;
	game->e->move_left = load_animation(game, enemy_fly, &game->e->enemy_anims, 1);
	set_types(game->e->enemy_anims, ENEMY);
}

void	load_gun(t_game *game)
{
	t_sprite	gun_idle;
	t_sprite	gun_walk;
	t_sprite	gun_roll;

	gun_idle = new_sprite("./textures/wep/idle_", 6, 100, 0);
	game->g->char_idle = load_animation(game, gun_idle, &game->g->char_anims, 1);
	gun_idle.mirrored = 1;
	game->g->char_idle_l = load_animation(game, gun_idle, &game->g->char_anims, 1);
	gun_walk = new_sprite("./textures/wep/walk_", 8, 100, 0);
	game->g->char_right = load_animation(game, gun_walk, &game->g->char_anims, 1);
	game->g->char_down = load_animation(game, gun_walk, &game->g->char_anims, 1);
	gun_walk.mirrored = 1;
	game->g->char_left = load_animation(game, gun_walk, &game->g->char_anims, 1);
	game->g->char_up = load_animation(game, gun_walk, &game->g->char_anims, 1);
	gun_roll = new_sprite("./textures/wep/roll_", 5, 100, 0);
	game->g->char_roll_right = load_animation(game, gun_roll, &game->g->char_anims, 1);
	gun_roll.mirrored = 1;
	game->g->char_roll_left = load_animation(game, gun_roll, &game->g->char_anims, 1);
	game->g->char_roll_left->full_cycle = true;
	game->g->char_roll_right->full_cycle = true;
	set_types(game->g->char_anims, COLL);
}

void	load_char_up(t_game *game)
{
	t_sprite	hair;
	t_sprite	head;
	t_sprite	walk;

	walk = new_sprite("./textures/full/walk_", 8, 100, 1);
	head = new_sprite("./textures/head/walk_", 8, 100, 1);
	hair = new_sprite("./textures/hair/walk_", 8, 100, 1);
	game->p->char_up = load_animation(game, walk, &game->p->char_anims, 1);
	game->p->head = load_animation(game, head, &game->p->char_anims, 0);
	game->p->hair = load_animation(game, hair, &game->p->char_anims, 0);
	color_anim(game->p->hair->frames, game->p->char_up->frames);
	add_to_anim_frames(game->p->char_up->frames, game->p->head->frames);
	add_to_anim_frames(game->p->char_up->frames, game->p->hair->frames);
	clear_anim(&game->p->hair);
	clear_anim(&game->p->head);
}

void	get_animations(t_game *game)
{
	t_sprite	char_idle;
	t_sprite	char_walk;
	t_sprite	char_roll;

	char_idle = new_sprite("./textures/full/idle_", 6, 100, 0);
	game->p->char_idle = load_animation(game, char_idle, &game->p->char_anims, 1);
	char_idle.mirrored = 1;
	game->p->char_idle_l = load_animation(game, char_idle, &game->p->char_anims, 1);
	char_walk = new_sprite("./textures/full/walk_", 8, 100, 0);
	game->p->char_right = load_animation(game, char_walk, &game->p->char_anims, 1);
	game->p->char_down = load_animation(game, char_walk, &game->p->char_anims, 1);
	char_walk.mirrored = 1;
	game->p->char_left = load_animation(game, char_walk, &game->p->char_anims, 1);
	char_roll = new_sprite("./textures/full/roll_", 5, 100, 0);
	game->p->char_roll_right = load_animation(game, char_roll, &game->p->char_anims, 1);
	char_roll.mirrored = 1;
	game->p->char_roll_left = load_animation(game, char_roll, &game->p->char_anims, 1);
	game->p->char_roll_left->full_cycle = true;
	game->p->char_roll_right->full_cycle = true;
	load_char_up(game);
	set_types(game->p->char_anims, PLAYER);
	load_gun(game);
	load_enemy(game);
}

void	load_tiles(t_game *game, t_list **type, char *path, int img_count)
{
	t_list		*list;
	mlx_image_t	*img;
	int			i;

	i = 0;
	while (i < img_count)
	{
		img = get_img(game, path, i, 0);
		if (type == &game->coll_imgs)
		{
			if (!mlx_resize_image(img, game->coll_size, game->coll_size))
				error();
		}
		else if (type == &game->exit_imgs)
		{
			if (!mlx_resize_image(img, game->exit_size, game->exit_size))
				error();
		}
		else
		{
			if (!mlx_resize_image(img, game->tile_size, game->tile_size))
				error();
		}
		list = safe_lstnew(img);
		ft_lstadd_back(type, list);
		i++;
	}
}

void	load_map_textures(t_game *game)
{
	load_tiles(game, &game->wall_imgs, "./textures/wall/", WALL_C);
	load_tiles(game, &game->free_imgs, "./textures/free/", FREE_C);
	load_tiles(game, &game->exit_imgs, "./textures/exit/", EXIT_C);
	load_tiles(game, &game->coll_imgs, "./textures/coll/", COLL_C);

}
