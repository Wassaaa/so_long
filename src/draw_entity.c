/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:08:36 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 06:29:08 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static t_entity	*build_enemy(t_game *game)
{
	t_entity	*enemy;

	enemy = safe_ft_calloc(1, sizeof(t_entity));
	*enemy = *game->e;
	enemy->movement = safe_ft_calloc(1, sizeof(t_movement));
	build_anims(game->e, enemy);
	enemy->current = enemy->anims[A_RIGHT];
	return (enemy);
}

void	draw_enemy(t_game *game, t_map_element *el)
{
	mlx_image_t	*enemy_bg;
	mlx_image_t	*base_img;
	t_entity	*enemy;
	int			x;
	int			y;

	enemy = build_enemy(game);
	enemy->pos.x = el->x;
	enemy->pos.y = el->y;
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	enemy_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, enemy_bg, x, y);
	if (el->bg_instance == -1)
		error(EXIT_FAILURE, E_MLX);
	mlx_set_instance_depth(&enemy_bg->instances[el->bg_instance], FREE);
	x += enemy->off.x;
	y += enemy->off.y;
	draw_anims(game->mlx, enemy, x, y);
	base_img = (mlx_image_t *)(enemy->anims[A_RIGHT]->frames->content);
	enemy->base = base_img->instances[enemy->anims[A_RIGHT]->instance];
	ft_lstadd_back(&game->enemies, safe_lstnew(enemy));
	el->type = FREE;
}

void	draw_player(t_game *game, t_map_element *el)
{
	mlx_image_t	*p_bg;
	mlx_image_t	*base;
	int			x;
	int			y;

	game->p->current = game->p->anims[A_IDLE_R];
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	p_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, p_bg, x, y);
	if (el->bg_instance == -1)
		error(EXIT_FAILURE, E_MLX);
	game->p->current_el = el;
	mlx_set_instance_depth(&p_bg->instances[el->bg_instance], FREE);
	x += game->p->off.x;
	y += game->p->off.y;
	draw_anims(game->mlx, game->p, x, y);
	base = (mlx_image_t *)(game->p->anims[A_RIGHT]->frames->content);
	game->p->base = base->instances[game->p->anims[A_RIGHT]->instance];
	el->type = FREE;
}

void	draw_gun_anim(t_game *game)
{
	t_list			*temp;
	mlx_instance_t	*instance;
	mlx_instance_t	p_instance;
	mlx_image_t		*img;
	mlx_image_t		*p_img;

	game->g->current = game->g->anims[A_IDLE_R];
	draw_anims(game->mlx, game->g, game->p->pos.x, game->p->pos.y);
	fix_depth(game->g, &game->z);
	temp = game->g->anims[A_UP]->frames;
	while (temp)
	{
		img = (mlx_image_t *)temp->content;
		instance = &img->instances[game->g->anims[A_UP]->instance];
		p_img = (mlx_image_t *)game->p->anims[A_UP]->frames->content;
		p_instance = p_img->instances[game->p->anims[A_UP]->instance];
		mlx_set_instance_depth(instance, p_instance.z - 1);
		temp = temp->next;
	}
}
