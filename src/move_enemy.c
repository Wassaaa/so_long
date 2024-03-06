/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:15:25 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 01:19:30 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	enemy_move_to(t_game *game, t_entity *entity)
{
	static t_move	move[4] = {ent_up, ent_right, ent_down, ent_left};

	move[entity->movement->to](game, entity);
}

static void	keep_direction(t_game *game, t_entity *entity)
{
	enemy_move_to(game, entity);
	if (!entity->movement->active)
	{
		entity->movement->to = get_random() % 4;
		enemy_move_to(game, entity);
	}
}

void	move_enemy(t_game *game)
{
	t_list		*enemies;
	t_entity	*enemy;

	enemies = game->enemies;
	while (enemies)
	{
		enemy = (t_entity *)enemies->content;
		if (!enemy->movement->active && !win_lose(game))
			keep_direction(game, enemy);
		if (enemy->next)
			movement_animation(enemy);
		if (enemy->movement->active)
			move_image(enemy, game->mlx->delta_time);
		enemies = enemies->next;
	}
}
