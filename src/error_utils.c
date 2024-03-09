/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:29:16 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 01:59:28 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static char	*e_message(int err_v)
{
	static char	*error[E_MAX];
	static bool	init = false;

	if (!init)
	{
		error[E_MALLOC] = "Memory allocation failed";
		error[E_MAP] = "MAP: Error";
		error[E_MAP_BER] = "MAP: '.ber' extension required";
		error[E_MAP_ROUTE] = "MAP: No valid route";
		error[E_MAP_WALL] = "MAP: not surrounded by walls";
		error[E_MAP_RECT] = "MAP: not a rectangle";
		error[E_MAP_EL] = "MAP: Wrong symbols in map";
		error[E_MAP_PLAYERS] = "MAP: too many/few Players";
		error[E_MAP_COLLS] = "MAP: Not enough Collectibles";
		error[E_MAP_EXITS] = "MAP: too many/few Exits";
		error[E_MAP_SIZE] = "MAP: too small";
		init = true;
	}
	return (error[err_v]);
}

void	err_msg(int ret, int msg)
{
	if (ret == EXIT_FAILURE)
	{
		ft_printf("Error\n");
		if (msg != E_MLX)
			ft_printf("%s", e_message(msg));
		else
			ft_printf("%s", mlx_strerror(mlx_errno));
	}
}

void	free_content(void *content)
{
	free(content);
	content = NULL;
}
