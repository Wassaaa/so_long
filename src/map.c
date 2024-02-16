/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:54:44 by aklein            #+#    #+#             */
/*   Updated: 2024/02/16 20:46:58 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	read_map(t_game *game, char *map_file)
{
	int		fd;
	char	*line;
	int		line_nr;

	line_nr = 0;
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_elements(game, line, line_nr);
		free(line);
		line = get_next_line(fd);
		line_nr++;
	}
	game->map->height = line_nr;
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
		el = ft_calloc(1, sizeof(t_map_element));
		el->type = get_el_type(*line);
		if (el->type == PLAYER)
		{
			game->map->char_x = x;
			game->map->char_y = y;
		}
		el->images = get_el_imgs(game, *line);
		el->x = x++;
		el->y = y;
		ft_lstadd_back(&game->map->elements, safe_lstnew(el));
		line++;
	}
	game->map->width = x;
}
