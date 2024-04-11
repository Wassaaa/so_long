/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:54:44 by aklein            #+#    #+#             */
/*   Updated: 2024/04/11 18:07:27 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	map_info(t_game *game, char *map_file)
{
	char	*line;
	int		len;

	game->fd = open(map_file, O_RDONLY);
	line = get_next_line(game->fd);
	if (!line)
		error(EXIT_FAILURE, E_MAP);
	game->map->width = ft_strlen(line) - 1;
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		if (len != game->map->width)
		{
			free(line);
			error(EXIT_FAILURE, E_MAP_RECT);
		}
		free(line);
		line = get_next_line(game->fd);
		game->map->height++;
	}
	close(game->fd);
	game->fd = -1;
}

static void	validate_tile_types(t_map *map)
{
	t_map_element	*el;
	t_list			*elements;

	elements = map->elements;
	while (elements)
	{
		el = (t_map_element *)elements->content;
		if (el->type == PLAYER)
			map->players++;
		if (el->type == COLL)
			map->colls++;
		if (el->type == EXIT)
			map->exits++;
		if (el->y == 0 && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		if (el->y == map->height - 1 && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		if (el->x == 0 && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		if (el->x == map->width - 1 && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		elements = elements->next;
	}
}

static void	check_tile_counts(t_map *map)
{
	if (map->players != 1)
		error(EXIT_FAILURE, E_MAP_PLAYERS);
	if (map->colls < 1)
		error(EXIT_FAILURE, E_MAP_COLLS);
	if (map->exits != 1)
		error(EXIT_FAILURE, E_MAP_EXITS);
}

static int	check_route(t_game *game, t_list *els, int index)
{
	static int		colls = 0;
	static int		exit = 0;
	t_map_element	*el;

	el = (t_map_element *)ft_lstget(els, index)->content;
	if (el->type == WALL)
		return (0);
	if (el->visited)
		return (0);
	if (el->type == COLL)
		colls++;
	if (el->type == EXIT)
		exit++;
	el->visited = 1;
	check_route(game, els, index - game->map->width);
	check_route(game, els, index + 1);
	check_route(game, els, index + game->map->width);
	check_route(game, els, index - 1);
	if (exit == 1 && colls == game->map->colls)
		return (1);
	return (0);
}

void	map_valdiation(t_game *game, char *map_file)
{
	int	player_pos;

	if (game->map->height * game->map->width < 15)
		error(EXIT_FAILURE, E_MAP_SIZE);
	read_map(game, map_file);
	validate_tile_types(game->map);
	check_tile_counts(game->map);
	player_pos = (game->p->pos.y * game->map->width) + game->p->pos.x;
	if (!check_route(game, game->map->elements, player_pos))
		error(EXIT_FAILURE, E_MAP_ROUTE);
}
