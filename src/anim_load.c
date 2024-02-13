/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:43:05 by aklein            #+#    #+#             */
/*   Updated: 2024/02/13 02:46:58 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_sprite	new_sprite(char *path, int f_cnt, int f_spd, uint32_t size)
{
	t_sprite	sprite;

	sprite.f_path = path;
	sprite.frame_count = f_cnt;
	sprite.frame_speed = f_spd;
	sprite.size = size;
	return (sprite);
}

mlx_image_t	*get_img(t_game *game, char *path, int i)
{
	char			*path_start;
	char			*nr;
	char			*full_path;
	mlx_texture_t	*texture;
	mlx_image_t		*new_frame;

	nr = ft_itoa(i);
	path_start = ft_strjoin(path, nr);
	if (!path_start)
		error();
	full_path = ft_strjoin(path_start, ".png");
	if (!full_path)
		error();
	texture = mlx_load_png(full_path);
	if (!texture)
		error();
	new_frame = mlx_texture_to_image(game->mlx, texture);
	if (!new_frame)
		error();
	free(path_start);
	free(full_path);
	free(nr);
	mlx_delete_texture(texture);
	return (new_frame);	
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
		new_img = get_img(game, sprite.f_path, i);
		if (!mlx_resize_image(new_img, sprite.size, sprite.size))
			error();
		if (!new_frame)
			error();
		new_frame = ft_lstnew(new_img);
		ft_lstadd_back(&anim->frames, new_frame);
		i++;
	}
	frames_to_window(game->mlx, anim->frames);
	return (anim);
}

void	get_animations(t_game *game)
{
	t_sprite	char_idle;
	t_sprite	char_walk;
	t_sprite	char_roll;

	char_idle = new_sprite("./assets/full/idle_", 6, 100, game->char_size);
	game->char_idle = load_animation(game, char_idle);
	char_walk = new_sprite("./assets/full/walk_", 8, 100, game->char_size);
	game->char_move = load_animation(game, char_walk);
	char_roll = new_sprite("./assets/full/roll_", 5, 100, game->char_size);
	game->char_roll = load_animation(game, char_roll);
}