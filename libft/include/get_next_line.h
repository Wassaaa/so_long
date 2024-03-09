/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:03:37 by aklein            #+#    #+#             */
/*   Updated: 2024/03/09 04:57:46 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# define MAX_FD 256

char	*get_next_line(int fd);
char	*append_str_to_str(char *str, char *src, int len);

#endif
