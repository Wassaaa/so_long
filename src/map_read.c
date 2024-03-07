/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:19:19 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:26:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int	get_el_type(char c)
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

static t_list	*get_el_imgs(t_game *game, char c)
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

static void	fill_elements(t_game *game, char *line, int y)
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
