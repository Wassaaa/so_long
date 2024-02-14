/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:54:44 by aklein            #+#    #+#             */
/*   Updated: 2024/02/15 01:13:33 by aklein           ###   ########.fr       */
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
}

int	get_el_type(char c)
{
	if (c == '0')
		return (EMPTY);
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

mlx_image_t	*get_el_img(t_game *game, char c)
{
	if (c == '0')
		return (game->free);
	if (c == '1')
		return (game->wall);
	if (c == 'C')
		return (game->coll);
	if (c == 'E')
		return (game->exit);
	if (c == 'P')
		return (game->free);
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
		el->img = get_el_img(game, *line);
		el->x = x++;
		el->y = y;
		ft_lstadd_back(&game->map->elements, safe_lstnew(el));
		line++;
	} 
}
