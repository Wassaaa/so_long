/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:08:09 by aklein            #+#    #+#             */
/*   Updated: 2024/02/19 19:39:24 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
void	null_content(void *content)
{
	content = NULL;
}

void error(void)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	clear_anim(t_anim **anim)
{
	t_anim	*animation;
	t_list	*frames;

	animation = *anim;
	frames = animation->frames;

	ft_lstclear(&frames, null_content);
	free(animation);
	animation = NULL;
	anim = NULL;
	return ;
}
