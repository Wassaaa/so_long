/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:10:05 by aklein            #+#    #+#             */
/*   Updated: 2024/02/25 18:22:05 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	do_idle(t_game *game)
{
	if (game->p->movement->to == DOWN || game->p->movement->to == RIGHT)
		game->p->next = game->p->anims[A_IDLE_R];
	else
		game->p->next = game->p->anims[A_IDLE_L];
}
