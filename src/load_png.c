/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:43:05 by aklein            #+#    #+#             */
/*   Updated: 2024/03/05 21:03:42 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	load_enemy(t_game *game)
{
	t_sprite	enemy_fly;

	enemy_fly = new_sprite("./textures/enemy/fly_", 6, 100, 0);
	game->e->anims[A_RIGHT] = load_animation(game, enemy_fly);
	game->e->anims[A_DOWN] = load_animation(game, enemy_fly);
	enemy_fly.mirrored = 1;
	game->e->anims[A_LEFT] = load_animation(game, enemy_fly);
	game->e->anims[A_UP] = load_animation(game, enemy_fly);
}

static void	load_gun(t_game *game)
{
	t_sprite	gun_idle;
	t_sprite	gun_walk;
	t_sprite	gun_roll;

	gun_idle = new_sprite("./textures/wep/idle_", 6, 100, 0);
	game->g->anims[A_IDLE_R] = load_animation(game, gun_idle);
	gun_idle.mirrored = 1;
	game->g->anims[A_IDLE_L] = load_animation(game, gun_idle);
	gun_walk = new_sprite("./textures/wep/walk_", 8, 100, 0);
	game->g->anims[A_RIGHT] = load_animation(game, gun_walk);
	game->g->anims[A_DOWN] = load_animation(game, gun_walk);
	gun_walk.mirrored = 1;
	game->g->anims[A_LEFT] = load_animation(game, gun_walk);
	game->g->anims[A_UP] = load_animation(game, gun_walk);
	gun_roll = new_sprite("./textures/wep/roll_", 5, 100, 0);
	game->g->anims[A_ROLL_R] = load_animation(game, gun_roll);
	gun_roll.mirrored = 1;
	game->g->anims[A_ROLL_L] = load_animation(game, gun_roll);
	game->g->anims[A_ROLL_R]->full_cycle = true;
	game->g->anims[A_ROLL_L]->full_cycle = true;
}

static void	load_char_up(t_game *game)
{
	t_sprite	hair;
	t_sprite	head;
	t_sprite	walk;
	t_anim		*head_anim;
	t_anim		*hair_anim;

	walk = new_sprite("./textures/full/walk_", 8, 100, 1);
	head = new_sprite("./textures/head/walk_", 8, 100, 1);
	hair = new_sprite("./textures/hair/walk_", 8, 100, 1);
	game->p->anims[A_UP] = load_animation(game, walk);
	head_anim = load_animation(game, head);
	hair_anim = load_animation(game, hair);
	color_anim(hair_anim->frames, game->p->anims[A_UP]->frames);
	anim_to_anim(game->p->anims[A_UP]->frames, head_anim->frames);
	anim_to_anim(game->p->anims[A_UP]->frames, hair_anim->frames);
	clear_anim(&hair_anim);
	clear_anim(&head_anim);
}

void	get_animations(t_game *game)
{
	t_sprite	char_idle;
	t_sprite	char_walk;
	t_sprite	char_roll;

	char_idle = new_sprite("./textures/full/idle_", 6, 100, 0);
	game->p->anims[A_IDLE_R] = load_animation(game, char_idle);
	char_idle.mirrored = 1;
	game->p->anims[A_IDLE_L] = load_animation(game, char_idle);
	char_walk = new_sprite("./textures/full/walk_", 8, 100, 0);
	game->p->anims[A_RIGHT] = load_animation(game, char_walk);
	game->p->anims[A_DOWN] = load_animation(game, char_walk);
	char_walk.mirrored = 1;
	game->p->anims[A_LEFT] = load_animation(game, char_walk);
	load_char_up(game);
	char_roll = new_sprite("./textures/full/roll_", 5, 100, 0);
	game->p->anims[A_ROLL_R] = load_animation(game, char_roll);
	char_roll.mirrored = 1;
	game->p->anims[A_ROLL_L] = load_animation(game, char_roll);
	game->p->anims[A_ROLL_L]->full_cycle = true;
	game->p->anims[A_ROLL_R]->full_cycle = true;
	load_gun(game);
	load_enemy(game);
}

void	load_map_textures(t_game *game)
{
	load_tiles(game, &game->wall_imgs, "./textures/wall/", WALL_C);
	load_tiles(game, &game->free_imgs, "./textures/free/", FREE_C);
	load_tiles(game, &game->exit_imgs, "./textures/exit/", EXIT_C);
	load_tiles(game, &game->coll_imgs, "./textures/coll/", COLL_C);
}
