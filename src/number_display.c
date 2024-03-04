/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 07:12:09 by aklein            #+#    #+#             */
/*   Updated: 2024/03/04 09:11:38 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	draw_digits(t_game *game, int i)
{
	int	new_nr;
	int	x;
	int	y;

	x = game->ui->info_x;
	y = game->ui->info_y;
	new_nr = mlx_image_to_window(game->mlx, game->ui->numbers[i], x - 10, y);
	if (new_nr == -1)
		error(EXIT_FAILURE, E_MLX);
	game->ui->tens = new_nr;
	game->ui->numbers[i]->instances[new_nr].enabled = false;
	new_nr = mlx_image_to_window(game->mlx, game->ui->numbers[i], x - 20, y);
	if (new_nr == -1)
		error(EXIT_FAILURE, E_MLX);
	game->ui->hundreds = new_nr;
	game->ui->numbers[i]->instances[new_nr].enabled = false;
	new_nr = mlx_image_to_window(game->mlx, game->ui->numbers[i], x - 30, y);
	if (new_nr == -1)
		error(EXIT_FAILURE, E_MLX);
	game->ui->thousands = new_nr;
	game->ui->numbers[i]->instances[new_nr].enabled = false;
}

void	generate_number_imgs(t_game *game)
{
	int			i;
	char		*nr;
	int			x;
	int			y;

	x = game->ui->info_x;
	y = game->ui->info_y;
	i = 0;
	while (i < 10)
	{
		nr = ft_itoa(i);
		if (!nr)
			error(EXIT_FAILURE, E_MALLOC);
		game->ui->numbers[i] = mlx_put_string(game->mlx, nr, x, y);
		game->ui->numbers[i]->instances[0].enabled = false;
		game->ui->units = 0;
		draw_digits(game, i);
		free(nr);
		i++;
	}
	game->ui->numbers[4]->instances[game->ui->tens].enabled = true;
	game->ui->numbers[2]->instances[game->ui->units].enabled = true;

}
