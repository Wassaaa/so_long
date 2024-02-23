/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:47:44 by aklein            #+#    #+#             */
/*   Updated: 2024/02/23 23:12:52 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	update_animation(t_anim *a, double dt)
{
	if (a)
	{
		a->accum += dt * 1000;
		if (a->accum > a->frame_speed * 2)
			a->accum = a->frame_speed + 1;
		if (a->accum > a->frame_speed)
		{
			a->accum -= a->frame_speed;
			a->cur_f++;
			a->cur_f %= a->frame_count;
			return (1);
		}
	}
	return (0);
}

void	animate_character(t_anim *anim, double dt)
{
	mlx_image_t *img;

	img = ft_lstget(anim->frames, anim->cur_f)->content;
	img->instances[anim->instance].enabled = false;
	if (anim->is_active)
	{
		if (update_animation(anim, dt))
			img = ft_lstget(anim->frames, anim->cur_f)->content;
		img->instances[anim->instance].enabled = true;
	}
}

void	enemy_animations(t_list *enemies, double dt)
{
	t_entity *enemy;
	while (enemies)
	{
		enemy = (t_entity *)enemies->content;
		animate_character(enemy->current, dt);
		enemies = enemies->next;
	}
}

void	roll_animations(t_game *game)
{
	animate_character(game->p->current, game->mlx->delta_time);
	animate_character(game->g->current, game->mlx->delta_time);
	enemy_animations(game->enemies, game->mlx->delta_time);

}
