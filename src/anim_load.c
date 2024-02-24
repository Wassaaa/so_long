/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:43:05 by aklein            #+#    #+#             */
/*   Updated: 2024/02/24 03:13:53 by aklein           ###   ########.fr       */
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

char	*build_path(int i, char *path)
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

t_anim	*load_animation(t_game *game, t_sprite sprite, t_list **anim_base,
		int list)
{
	t_anim		*anim;
	int			i;
	mlx_image_t	*new_img;

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

void	load_enemy(t_game *game)
{
	t_sprite	enemy_fly;

	enemy_fly = new_sprite("./textures/enemy/fly_", 6, 100, 0);
	game->e->right = load_animation(game, enemy_fly, &game->e->anims, 1);
	enemy_fly.mirrored = 1;
	game->e->left = load_animation(game, enemy_fly, &game->e->anims, 1);
	set_types(game->e->anims, ENEMY);
}

void	load_gun(t_game *game)
{
	t_sprite	gun_idle;
	t_sprite	gun_walk;
	t_sprite	gun_roll;

	gun_idle = new_sprite("./textures/wep/idle_", 6, 100, 0);
	game->g->idle_r = load_animation(game, gun_idle, &game->g->anims, 1);
	gun_idle.mirrored = 1;
	game->g->idle_l = load_animation(game, gun_idle, &game->g->anims, 1);
	gun_walk = new_sprite("./textures/wep/walk_", 8, 100, 0);
	game->g->right = load_animation(game, gun_walk, &game->g->anims, 1);
	game->g->down = load_animation(game, gun_walk, &game->g->anims, 1);
	gun_walk.mirrored = 1;
	game->g->left = load_animation(game, gun_walk, &game->g->anims, 1);
	game->g->up = load_animation(game, gun_walk, &game->g->anims, 1);
	gun_roll = new_sprite("./textures/wep/roll_", 5, 100, 0);
	game->g->roll_r = load_animation(game, gun_roll, &game->g->anims, 1);
	gun_roll.mirrored = 1;
	game->g->roll_l = load_animation(game, gun_roll, &game->g->anims, 1);
	game->g->roll_r->full_cycle = true;
	game->g->roll_l->full_cycle = true;
	set_types(game->g->anims, COLL);
}

void	load_char_up(t_game *game)
{
	t_sprite	hair;
	t_sprite	head;
	t_sprite	walk;
	t_anim		*head_anim;
	t_anim		*hair_anim;

	walk = new_sprite("./textures/full/walk_", 8, 100, 1);
	head = new_sprite("./textures/head/walk_", 8, 100, 1);
	hair = new_sprite("./textures/hair/walk_", 8, 100, 1);
	game->p->up = load_animation(game, walk, &game->p->anims, 1);
	head_anim = load_animation(game, head, NULL, 0);
	hair_anim = load_animation(game, hair, NULL, 0);
	color_anim(hair_anim->frames, game->p->up->frames);
	add_to_anim_frames(game->p->up->frames, head_anim->frames);
	add_to_anim_frames(game->p->up->frames, hair_anim->frames);
	clear_anim(&hair_anim);
	clear_anim(&head_anim);
}

void	get_animations(t_game *game)
{
	t_sprite	char_idle;
	t_sprite	char_walk;
	t_sprite	char_roll;

	char_idle = new_sprite("./textures/full/idle_", 6, 100, 0);
	game->p->idle_r = load_animation(game, char_idle, &game->p->anims, 1);
	char_idle.mirrored = 1;
	game->p->idle_l = load_animation(game, char_idle, &game->p->anims, 1);
	char_walk = new_sprite("./textures/full/walk_", 8, 100, 0);
	game->p->right = load_animation(game, char_walk, &game->p->anims, 1);
	game->p->down = load_animation(game, char_walk, &game->p->anims, 1);
	char_walk.mirrored = 1;
	game->p->left = load_animation(game, char_walk, &game->p->anims, 1);
	load_char_up(game);
	char_roll = new_sprite("./textures/full/roll_", 5, 100, 0);
	game->p->roll_r = load_animation(game, char_roll, &game->p->anims, 1);
	char_roll.mirrored = 1;
	game->p->roll_l = load_animation(game, char_roll, &game->p->anims, 1);
	game->p->roll_l->full_cycle = true;
	game->p->roll_r->full_cycle = true;
	set_types(game->p->anims, PLAYER);
	load_gun(game);
	load_enemy(game);
}

void	load_tiles(t_game *game, t_list **type_lst, char *path, int img_count)
{
	t_list		*list;
	mlx_image_t	*img;
	int			i;

	i = 0;
	while (i < img_count)
	{
		img = get_img(game, path, i, 0);
		if (type_lst == &game->coll_imgs)
		{
			if (!mlx_resize_image(img, game->coll_size, game->coll_size))
				error();
		}
		else if (type_lst == &game->exit_imgs)
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
		ft_lstadd_back(type_lst, list);
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
