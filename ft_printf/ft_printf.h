/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 00:58:39 by aklein            #+#    #+#             */
/*   Updated: 2023/11/14 21:03:21 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define SPECS "cspdiuxX%"
# define HEXBASELOWER "0123456789abcdef"
# define HEXBASEUPPER "0123456789ABCDEF"

typedef struct s_print
{
	const char	*frm;
	va_list		ap;
	char		spec;
	int			printed;
	int			fd;
	int			spec_i;
}				t_print;

int				ft_printf(const char *frm, ...);
void			init_print(t_print *print);
void			reset_print(t_print *print);
int				parse_spec(t_print *print);
size_t			count_digits(int n);
size_t			count_digits_ui(unsigned int n);
size_t			count_digits_hex(unsigned long nb);
int				print_c(t_print *print);
int				print_s(t_print *print);
int				print_p(t_print *print);
int				print_d(t_print *print);
int				print_u(t_print *print);
int				print_x(t_print *print);
int				ft_safe_putnbr_base_ul_fd(unsigned long nbr, \
				char *base, int fd);
int				ft_safe_putnbr_ul_fd(unsigned long n, int fd);
int				ft_safe_putnbr_fd(int n, int fd);
int				ft_safe_putchar_fd(char c, int fd);
int				ft_safe_putstr_fd(char *s, int fd);
#endif
