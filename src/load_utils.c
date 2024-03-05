/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:50:24 by aklein            #+#    #+#             */
/*   Updated: 2024/03/05 21:01:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_sprite	new_sprite(char *path, int f_cnt, int f_spd, int mir)
{
	t_sprite	sprite;

	sprite.f_path = path;
	sprite.frame_count = f_cnt;
	sprite.frame_speed = f_spd;
	sprite.mirrored = mir;
	return (sprite);
}

static char	*build_path(int i, char *path)
{
	char	*nr;
	char	*path_start;
	char	*full_path;

	nr = ft_itoa(i);
	path_start = ft_strjoin(path, nr);
	if (!path_start)
		error(EXIT_FAILURE, E_MALLOC);
	full_path = ft_strjoin(path_start, ".png");
	if (!full_path)
		error(EXIT_FAILURE, E_MALLOC);
	free(path_start);
	free(nr);
	return (full_path);
}

static mlx_image_t	*get_img(t_game *game, char *path, int i, int mirr)
{
	char			*full_path;
	mlx_texture_t	*texture;
	mlx_image_t		*new_img;
	mlx_image_t		*mirrored;

	full_path = build_path(i, path);
	texture = mlx_load_png(full_path);
	if (!texture)
		error(EXIT_FAILURE, E_MLX);
	new_img = mlx_texture_to_image(game->mlx, texture);
	if (!new_img)
		error(EXIT_FAILURE, E_MLX);
	if (!mlx_resize_image(new_img, game->char_size, game->char_size))
		error(EXIT_FAILURE, E_MLX);
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

t_anim	*load_animation(t_game *game, t_sprite sprite)
{
	t_anim		*anim;
	int			i;
	mlx_image_t	*new_img;

	anim = safe_ft_calloc(1, sizeof(t_anim));
	anim->frame_speed = sprite.frame_speed;
	anim->frame_count = sprite.frame_count;
	i = 0;
	while (i < sprite.frame_count)
	{
		new_img = get_img(game, sprite.f_path, i++, sprite.mirrored);
		ft_lstadd_back(&anim->frames, safe_lstnew(new_img));
	}
	return (anim);
}

void	load_tiles(t_game *game, t_list **lst, char *pth, int len)
{
	mlx_image_t	*img;
	int			i;

	i = 0;
	while (i < len)
	{
		img = get_img(game, pth, i++, 0);
		if (lst == &game->coll_imgs)
		{
			if (!mlx_resize_image(img, game->coll_size, game->coll_size))
				error(EXIT_FAILURE, E_MLX);
		}
		else if (lst == &game->exit_imgs)
		{
			if (!mlx_resize_image(img, game->exit_size, game->exit_size))
				error(EXIT_FAILURE, E_MLX);
		}
		else
		{
			if (!mlx_resize_image(img, game->tile_size, game->tile_size))
				error(EXIT_FAILURE, E_MLX);
		}
		ft_lstadd_back(lst, safe_lstnew(img));
	}
}
