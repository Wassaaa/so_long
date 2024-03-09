/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:54:25 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 05:34:38 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	get_ui(t_game *game)
{
	mlx_texture_t	*tex;
	int				x;
	int				y;

	fix_ui_sizes(game);
	x = (game->mlx->width / 2) - (game->ui->w / 2);
	y = game->tile_size / 10;
	game->ui->info_x = x + (game->ui->w / 2);
	game->ui->info_y = y + (game->ui->h / 2) - (20 * game->ui->sc);
	tex = mlx_load_png("./textures/ui/banner.png");
	if (!tex)
		error(EXIT_FAILURE, E_MLX);
	game->ui->bg = mlx_texture_to_image(game->mlx, tex);
	if (!game->ui->bg)
		error(EXIT_FAILURE, E_MLX);
	if (!mlx_resize_image(game->ui->bg, game->ui->w, game->ui->h))
		error(EXIT_FAILURE, E_MLX);
	if (mlx_image_to_window(game->mlx, game->ui->bg, x, y) == -1)
		error(EXIT_FAILURE, E_MLX);
	game->ui->bg->enabled = false;
	mlx_delete_texture(tex);
	ft_printf("\e[2;1HMoves: [%d]\e[K\n", game->moves);
	ft_printf("\e[3;1HCollectables: [%d]\e[K\n", game->map->colls);
}

static mlx_image_t	*info_str(t_game *game, char *str, int y_off)
{
	mlx_image_t	*img;
	t_point		loc;
	int			height;
	int			width;

	loc.x = game->ui->info_x - ((ft_strlen(str) * 10 * game->ui->sc));
	loc.y = game->ui->info_y + (y_off * game->ui->sc);
	img = mlx_put_string(game->mlx, str, loc.x, loc.y);
	if (!img)
		error(EXIT_FAILURE, E_MLX);
	height = img->height * game->ui->sc;
	if (height < 1)
		height = 1;
	width = img->width * game->ui->sc;
	if (width < 1)
		width = 1;
	if (!mlx_resize_image(img, width, height))
		error(EXIT_FAILURE, E_MLX);
	return (img);
}

static void	scale_numbers(t_game *game)
{
	int		i;
	int		width;
	int		height;
	float	sc;

	i = 0;
	sc = game->ui->sc;
	while (i < 10)
	{
		width = game->ui->numbers[i]->width * sc;
		if (width < 1)
			width = 1;
		height = game->ui->numbers[i]->height * sc;
		if (height < 1)
			height = 1;
		if (!mlx_resize_image(game->ui->numbers[i], width, height))
			error(EXIT_FAILURE, E_MLX);
		i++;
	}
}

void	game_ui(t_game *game)
{
	static int	box = 0;

	if (!box)
	{
		box = 1;
		get_ui(game);
		game->ui->bg->enabled = true;
		game->ui->moves = info_str(game, "Moves:", 0);
		generate_number_imgs(game);
	}
	game->ui->moves_loc.x = game->ui->moves->instances[0].x
		+ game->ui->moves->width;
	game->ui->moves_loc.y = game->ui->moves->instances[0].y;
	scale_numbers(game);
	got_gun(game);
	display_number(game, game->moves, game->ui->moves_loc);
}
