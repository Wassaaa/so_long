/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:13:00 by aklein            #+#    #+#             */
/*   Updated: 2024/02/22 20:10:10 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	win_lose(t_game *game)
{
	if (game->game_status == 1)
		ft_printf("\e[4;1H\e[JVICTORY!");
	if (game->game_status == -1)
		ft_printf("\e[4;1H\e[JYOU DIED");
	if (game->game_status != 0)
		return (1);
	return (0);
}

void	show_fps(t_game *game)
{
	static int		fps = 1;
	static double	i = 0;
	static int		random;


	i += game->mlx->delta_time;
	random++;
	fps++;
	if (i >= 1)
	{
		game->fps = fps;
		if (game->fps < 30)
			game->fps = 60;
		ft_printf("\e[1;1H\e[2Jfps [%d]\n", fps);
		ft_printf("\e[2;1HMoves: [%d]\n", game->score);
		ft_printf("\e[3;1HCollectables: [%d]\n", game->map->colls);
		i = 0;
		fps = 0;
	}
	game->move_speed = (game->tile_size / game->fps) * SPEED;
	if (game->move_speed < 1)
		game->move_speed = 1 * SPEED;
	got_gun(game);
	game->random = random;
}
