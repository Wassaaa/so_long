/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:43:05 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 22:57:12 by aklein           ###   ########.fr       */
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

void	frames_to_window(mlx_t *mlx, t_list *frames)
{
	mlx_image_t	*frame;

	while (frames != NULL)
	{
		frame = (mlx_image_t *)frames->content;
		if (mlx_image_to_window(mlx, frame, 0, 0) < 0)
			error();
		frame->instances[0].enabled = false;
		frames = frames->next;
	}
}

t_anim	*load_animation(t_game *game, t_sprite sprite)
{
	t_anim			*anim;
	int				i;
	t_list			*new_frame;
	mlx_image_t		*new_img;

	anim = ft_calloc(1, sizeof(t_anim));
	if (!anim)
		error();
	anim->frame_speed = sprite.frame_speed;
	i = 0;
	while (i < sprite.frame_count)
	{
		new_img = get_img(game, sprite.f_path, i++, sprite.mirrored);
		if (!new_frame)
			error();
		new_frame = ft_lstnew(new_img);
		ft_lstadd_back(&anim->frames, new_frame);
	}
	frames_to_window(game->mlx, anim->frames);
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
//void (*f)(void *)
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

void	load_char_up(t_game *game)
{
	t_sprite	hair;
	t_sprite	head;
	t_sprite	walk;

	walk = new_sprite("./assets/full/walk_", 8, 100, 1);
	head = new_sprite("./assets/head/walk_", 8, 100, 1);
	hair = new_sprite("./assets/hair/walk_", 8, 100, 1);
	game->char_up = load_animation(game, walk);
	game->head = load_animation(game, head);
	game->hair = load_animation(game, hair);
	color_anim(game->hair->frames, game->char_up->frames);
	add_to_anim_frames(game->char_up->frames, game->head->frames);
	add_to_anim_frames(game->char_up->frames, game->hair->frames); 
}

void	get_animations(t_game *game)
{
	t_sprite	char_idle;
	t_sprite	char_walk;
	t_sprite	char_roll;

	char_idle = new_sprite("./assets/full/idle_", 6, 140, 0);
	game->char_idle = load_animation(game, char_idle);
	char_walk = new_sprite("./assets/full/walk_", 8, 100, 0);
	game->char_right = load_animation(game, char_walk);
	game->char_down = load_animation(game, char_walk);
	char_walk.mirrored = 1;
	game->char_left = load_animation(game, char_walk);
	char_roll = new_sprite("./assets/full/roll_", 5, 100, 0);
	game->char_roll_right = load_animation(game, char_roll);
	char_roll.mirrored = 1;
	game->char_roll_left = load_animation(game, char_roll);
	game->char_roll_right->one_cycle = true;
	game->char_roll_left->one_cycle = true;
	load_char_up(game);
}
