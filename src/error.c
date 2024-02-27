/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:08:09 by aklein            #+#    #+#             */
/*   Updated: 2024/02/27 04:42:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	free_content(void *content)
{
	free(content);
	content = NULL;
}

void	clear_ent(void *ent)
{
	int			i;
	t_entity	*entity;

	i = 0;
	entity = (t_entity *)ent;
	if (!entity)
		return ;
	while (i < A_COUNT)
	{
		if (entity->anims[i])
			clear_anim(&entity->anims[i]);
		i++;
	}
	if (entity->movement)
	{
		free(entity->movement);
		entity->movement = NULL;
	}
	ft_bzero(entity, sizeof(t_entity));
	free(entity);
	entity = NULL;
	ent = NULL;
}

void	clear_anim(t_anim **anim)
{
	t_anim	*animation;
	t_list	*frames;

	animation = *anim;
	frames = animation->frames;
	if (frames)
		ft_lstclear(&frames, NULL);
	free(animation);
	animation = NULL;
	anim = NULL;
	return ;
}

void	clear_map(t_map **map)
{
	ft_lstclear(&(*map)->elements, free_content);
	free(*map);
	*map = NULL;
	map = NULL;
}

void	clear_enemies(void *content)
{
	t_entity	*enemy;
	int			i;

	i = 0;
	enemy = (t_entity *)content;
	if (!enemy)
		return ;
	while (i < A_COUNT)
	{
		if (enemy->anims[i])
			free(enemy->anims[i]);
		i++;
	}
	if (enemy->movement)
	{
		free(enemy->movement);
		enemy->movement = NULL;
	}
	free(content);
	content = NULL;
}

void	error(void)
{
	t_game	*game;

	game = *get_game();
	if (game->fd >= 0)
		close (game->fd);
	clear_map(&game->map);
	clear_ent(game->p);
	clear_ent(game->g);
	clear_ent(game->e);
	ft_lstclear(&game->enemies, clear_enemies);
	ft_lstclear(&game->wall_imgs, NULL);
	ft_lstclear(&game->free_imgs, NULL);
	ft_lstclear(&game->exit_imgs, NULL);
	ft_lstclear(&game->coll_imgs, NULL);
	mlx_terminate(game->mlx);
	ft_printf("%s", mlx_strerror(mlx_errno));
	free(game);
	game = NULL;
	exit(EXIT_FAILURE);
}
