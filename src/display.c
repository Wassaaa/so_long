/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:13:00 by aklein            #+#    #+#             */
/*   Updated: 2024/03/05 00:42:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	win_lose(t_game *game)
{
	static int game_over = 0;

	if (!game_over)
	{
		if (game->game_status == 1)
		{
			ft_printf("\e[4;1H\e[KVICTORY!");
		}
		if (game->game_status == -1)
		{
			ft_printf("\e[4;1H\e[KYOU DIED");
		}
		if (game->game_status != 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

void	show_fps(t_game *game)
{
	static int		fps = 1;
	static double	i = 0;


	i += game->mlx->delta_time;
	fps++;
	if (i >= 1)
	{
		game->fps = fps;
		if (game->fps < 30)
			game->fps = 60;
		ft_printf("\e[1;1Hfps [%d]\e[K\n", fps);
		i = 0;
		fps = 0;
	}
}
