/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 07:12:09 by aklein            #+#    #+#             */
/*   Updated: 2024/03/04 17:31:51 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	hide_numbers(t_ui *ui)
{
	size_t		i;
	size_t		j;
	mlx_image_t	*nb;

	i = 0;
	while (i < 10)
	{
		j = 0;
		nb = ui->numbers[i++];
		while (j < nb->count)
			nb->instances[j++].enabled = false;
	}
}

void	draw_digits(t_game *game, int nb_i)
{
	int	new_nr;
	int	i;

	i = 1;
	while (i < UI_MAX)
	{
		new_nr = mlx_image_to_window(game->mlx, game->ui->numbers[nb_i], 0, 0);
		if (new_nr == -1)
			error(EXIT_FAILURE, E_MLX);
		game->ui->nb_parts[i] = new_nr;
		i++;
	}
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
		game->ui->nb_parts[UNITS] = 0;
		draw_digits(game, i);
		free(nr);
		i++;
	}
	hide_numbers(game->ui);
}

void	display_number(t_game *game, int nb, int x, int y)
{
	size_t		digits[UI_MAX];
	size_t		place;
	size_t		i;
	mlx_image_t	*instance;

	i = 0;
	place = 0;
	hide_numbers(game->ui);
	while (nb > 0)
	{
		digits[place++] = nb % 10;
		nb /= 10;
	}
	while (place)
	{
		instance = game->ui->numbers[digits[i]];
		instance->instances[UI_MAX - place].enabled = true;
		instance->instances[UI_MAX - place].x = x + (10 * place);
		instance->instances[UI_MAX - place].y = y;
		place--;
		i++;
	}
}