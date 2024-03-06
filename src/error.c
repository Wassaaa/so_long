/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:08:09 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 01:34:21 by aklein           ###   ########.fr       */
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

char	*e_message(int err_v)
{
	static char *error[E_MAX];
	static bool	init = false;

	if (!init)
	{
		error[E_MALLOC] = "Memory allocation failed";
		error[E_MAP] = "MAP: Error";
		error[E_MAP_ROUTE] = "MAP: No valid route";
		error[E_MAP_WALL] = "MAP: not surrounded by walls";
		error[E_MAP_RECT] = "MAP: not a rectangle";
		error[E_MAP_EL] = "MAP: Wrong symbols in map";
		error[E_MAP_PLAYERS] = "MAP: too many/few Players";
		error[E_MAP_COLLS] = "MAP: Not enough Collectibles";
		error[E_MAP_EXITS] = "MAP: too many/few Exits";
		error[E_MAP_SIZE] = "MAP: too small";
		init = true;
	}
	return (error[err_v]);
}

void	err_msg(int ret, int msg)
{
	if (ret == EXIT_FAILURE)
	{
		ft_printf("Error\n");
		if (msg != E_MLX)
			ft_printf("%s", e_message(msg));
		else
			ft_printf("%s", mlx_strerror(mlx_errno));
	}
}

void	error(int ret, int msg)
{
	t_game	*game;

	game = *get_game();
	if (game->fd >= 0)
		close (game->fd);
	clear_map(&game->map);
	free_content(game->ui);
	clear_ent(game->p);
	clear_ent(game->g);
	clear_ent(game->e);
	ft_lstclear(&game->enemies, clear_enemies);
	ft_lstclear(&game->wall_imgs, NULL);
	ft_lstclear(&game->free_imgs, NULL);
	ft_lstclear(&game->exit_imgs, NULL);
	ft_lstclear(&game->coll_imgs, NULL);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game);
	game = NULL;
	if (ret == EXIT_FAILURE)
		err_msg(ret, msg);
	exit(ret);
}
