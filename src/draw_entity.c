/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:08:36 by aklein            #+#    #+#             */
/*   Updated: 2024/02/26 23:09:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static t_entity	*build_enemy(t_game *game)
{
	t_entity *enemy;

	enemy = ft_calloc(1, sizeof(t_entity));
	if (!enemy)
		error();
	*enemy = *game->e;
	enemy->movement = ft_calloc(1, sizeof(t_movement));
	if (!enemy->movement)
		error();
	build_anims(game->e, enemy);
	enemy->current = enemy->anims[A_RIGHT];
	return (enemy);
}

void	draw_enemy(t_game *game, t_map_element *el)
{
	mlx_image_t 	*enemy_bg;
	mlx_image_t		*base_img;
	t_entity		*enemy;
	int				x;
	int				y;
	static int		index = 0;

	enemy = build_enemy(game);
	enemy->pos.x = el->x;
	enemy->pos.y = el->y;
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	enemy_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, enemy_bg, x, y);
	mlx_set_instance_depth(&enemy_bg->instances[el->bg_instance], FREE);
	x += enemy->off.x;
	y += enemy->off.y;
	draw_anims(game->mlx, enemy, x, y);
	base_img = (mlx_image_t *)(enemy->anims[A_RIGHT]->frames->content);
	enemy->base = base_img->instances[enemy->anims[A_RIGHT]->instance];
	enemy->index = index++;
	ft_lstadd_back(&game->enemies, safe_lstnew(enemy));
}

void	draw_player(t_game *game, t_map_element *el)
{
	mlx_image_t *player_bg;
	mlx_image_t	*base;
	int			x;
	int			y;

	game->p->current = game->p->anims[A_IDLE_R];
	game->p->pos.x = el->x;
	game->p->pos.y = el->y;
	x = el->x * game->tile_size;
	y = el->y * game->tile_size;
	player_bg = ft_lstget(game->free_imgs, get_random() % (FREE_C - 1))->content;
	el->bg_instance = mlx_image_to_window(game->mlx, player_bg, x, y);
	mlx_set_instance_depth(&player_bg->instances[el->bg_instance], FREE);
	x += game->p->off.x;
	y += game->p->off.y;
	draw_anims(game->mlx, game->p, x, y);
	base = (mlx_image_t *)(game->p->anims[A_RIGHT]->frames->content);
	game->p->base = base->instances[game->p->anims[A_RIGHT]->instance];
}
void	draw_gun_anim(t_game *game)
{
	int				x;
	int				y;
	t_list			*temp;
	mlx_instance_t	*instance;
	mlx_instance_t	p_instance;
	mlx_image_t		*img;
	mlx_image_t		*p_img;

	game->g->current = game->g->anims[A_IDLE_R];
	x = game->p->pos.x;
	y = game->p->pos.y;
	draw_anims(game->mlx, game->g, x, y);
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