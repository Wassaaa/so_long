/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:54:44 by aklein            #+#    #+#             */
/*   Updated: 2024/02/28 00:36:45 by aklein           ###   ########.fr       */
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
		error();
	game->map->width = ft_strlen(line) - 1;
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		if (len != game->map->width)
		{
			free(line);
			error();
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
		error();
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
			error();
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
			error();
		if (el->y == map->height && el->type != WALL)
			error();
		if (el->x == 0 && el->type != WALL)
			error();
		if (el->x == map->width && el->type != WALL)
			error();
		elements = elements->next;
	}
}

void	check_tile_counts(t_map *map)
{
	if (map->players != 1)
		error();
	if (map->colls < 1)
		error();
	if (map->exits != 1)
		error();
}

void	map_valdiation(t_game *game, char *map_file)
{
	check_rectangle(game, map_file);
	if (game->map->height < 3 || game->map->width < 5)
		error();
	read_map(game, map_file);
	validate_tile_types(game->map);
	check_tile_counts(game->map);
}