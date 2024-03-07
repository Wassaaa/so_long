/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:14:00 by aklein            #+#    #+#             */
/*   Updated: 2024/03/07 19:11:24 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	*safe_ft_calloc(size_t count, size_t size)
{
	void	*my_calloc;

	my_calloc = ft_calloc(count, size);
	if (!my_calloc)
		error(EXIT_FAILURE, E_MALLOC);
	return (my_calloc);
}

t_list	*safe_lstnew(void *content)
{
	t_list	*frame;

	frame = ft_lstnew(content);
	if (!frame)
		error(EXIT_FAILURE, E_MALLOC);
	return (frame);
}

size_t	get_random(void)
{
	int			fd;
	static int	not_so_random = 0;
	size_t		buff;

	not_so_random++;
	buff = not_so_random;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd > -1)
	{
		read(fd, &buff, sizeof(size_t));
		close(fd);
	}
	return (buff);
}
