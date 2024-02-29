/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:54:44 by aklein            #+#    #+#             */
/*   Updated: 2024/02/29 21:10:40 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	check_rectangle(t_game *game, char *map_file)
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

void	read_map(t_game *game, char *map_file)
{
	char	*line;
	int		y;

	y = 0;
	game->fd = open(map_file, O_RDONLY);
	line = get_next_line(game->fd);
	if (!line)
		error(EXIT_FAILURE, E_MAP);
	while (line != NULL)
	{
		fill_elements(game, line, y);
		free(line);
		line = get_next_line(game->fd);
		y++;
	}
	close(game->fd);
	game->fd = -1;
}

int	get_el_type(char c)
{
	if (c == '0')
		return (FREE);
	if (c == '1')
		return (WALL);
	if (c == 'C')
		return (COLL);
	if (c == 'E')
		return (EXIT);
	if (c == 'P')
		return (PLAYER);
	if (c == 'X')
		return (ENEMY);
	return (-1);
}

t_list	*get_el_imgs(t_game *game, char c)
{
	if (c == '0')
		return (game->free_imgs);
	if (c == '1')
		return (game->wall_imgs);
	if (c == 'C')
		return (game->coll_imgs);
	if (c == 'E')
		return (game->exit_imgs);
	if (c == 'P')
		return (game->free_imgs);
	return (NULL);
}

void	fill_elements(t_game *game, char *line, int y)
{
	t_map_element	*el;
	int				x;

	x = 0;
	while (*line)
	{
		if (*line == '\n')
			break ;
		el = safe_ft_calloc(1, sizeof(t_map_element));
		el->type = get_el_type(*line);
		if (el->type == -1)
			error(EXIT_FAILURE, E_MAP_EL);
		if (el->type == PLAYER)
		{
			game->p->pos.x = x;
			game->p->pos.y = y;
		}
		el->images = get_el_imgs(game, *line);
		el->x = x++;
		el->y = y;
		ft_lstadd_back(&game->map->elements, safe_lstnew(el));
		line++;
	}
}

void	validate_tile_types(t_map	*map)
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
		if (el->y == map->height && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		if (el->x == 0 && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		if (el->x == map->width && el->type != WALL)
			error(EXIT_FAILURE, E_MAP_WALL);
		elements = elements->next;
	}
}

void	check_tile_counts(t_map *map)
{
	if (map->players != 1)
		error(EXIT_FAILURE, E_MAP_PLAYERS);
	if (map->colls < 1)
		error(EXIT_FAILURE, E_MAP_COLLS);
	if (map->exits != 1)
		error(EXIT_FAILURE, E_MAP_EXITS);
}

int	check_route(t_game *game, t_list *els, int index)
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

	check_rectangle(game, map_file);
	if (game->map->height < 3 || game->map->width < 5)
		error(EXIT_FAILURE, E_MAP_SIZE);
	read_map(game, map_file);
	validate_tile_types(game->map);
	check_tile_counts(game->map);
	player_pos = (game->p->pos.y * game->map->width) + game->p->pos.x;
	if (!check_route(game, game->map->elements, player_pos))
		error(EXIT_FAILURE, E_MAP_ROUTE);
}