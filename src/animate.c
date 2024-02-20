/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:47:44 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 22:50:17 by aklein           ###   ########.fr       */
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
	img->instances[0].enabled = false;
	if (anim->is_active)
	{
		if (update_animation(anim, dt))
			img = ft_lstget(anim->frames, anim->cur_f)->content;
		img->instances[0].enabled = true;
	}
}

void	roll_animations(t_game *game)
{
	animation_loop(game->p->char_anims, game->mlx->delta_time);
	animation_loop(game->g->char_anims, game->mlx->delta_time);
}

void	animation_loop(t_list *anims, double dt)
{
	t_anim	*anim;

	while (anims != NULL)
	{
		anim = (t_anim *)anims->content;
		animate_character(anim, dt);
		anims = anims->next;
	}
}

void	toggle_states(t_game *game, t_list *anims, t_anim *current)
{
	t_list	*temp_anims;
	t_anim	*iter;
	t_anim	*current_one;

	temp_anims = anims;
	current_one = NULL;
	while (temp_anims != NULL)
	{
		iter = (t_anim *)temp_anims->content;
		if (iter->is_active && iter->full_cycle)
			ft_lstadd_back(&game->prio, safe_lstnew(iter));
		else if (iter == current)
		{
			current_one = iter;
			iter->is_active = true;
		}
		else
			iter->is_active = false;
		temp_anims = temp_anims->next;
	}
	if (game->prio && current_one)
		current_one->is_active = false;
}