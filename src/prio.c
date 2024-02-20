/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prio.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:05:03 by aklein            #+#    #+#             */
/*   Updated: 2024/02/20 22:29:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	finish_prio(t_game *game)
{
	t_anim	*prio;
	t_list	*prio_list;
	int		finished;

	finished = 0;
	if (game->prio)
	{
		prio_list = game->prio;
		while (prio_list)
		{
			prio = (t_anim *)prio_list->content;
			if (prio->cur_f != prio->frame_count - 1)
				prio->is_active = true;
			else
			{
				finished = 1;
				prio->is_active = false;
			}
			prio_list = prio_list->next;
		}
		if (finished)
			ft_lstclear(&game->prio, NULL);
	}
}