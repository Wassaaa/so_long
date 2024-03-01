# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 16:17:19 by aklein            #+#    #+#              #
#    Updated: 2024/03/01 20:12:56 by aklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		=	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\

FT_PF_SRC	=	ft_printf.c \
				ft_safe_putnbr_base_ul_fd.c \
				ft_safe_putnbr_ul_fd.c \
				ft_safe_putnbr_fd.c \
				ft_safe_putchar_fd.c \
				ft_safe_putstr_fd.c \
				prf_print_c.c \
				prf_print_s.c \
				prf_print_p.c \
				prf_print_d.c \
				prf_print_u.c \
				prf_print_x.c \
				prf_parse_spec.c \
				prf_init_print.c \
				count_digits.c \

GNL_SRC		=	get_next_line.c\
				get_next_line_utils.c

################################################################################
# GENERAL
################################################################################
OBJ_DIR		=	./obj
INCLUDES	=	./include

################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
CC_DEBUG		=	-g #-fsanitize=leak
HEADERS			=	-I $(INCLUDES)
CC_FULL			=	$(CC) $(CC_STRICT) $(HEADERS) $(CC_DEBUG)

################################################################################
# LIBFT
################################################################################
NAME 		=	libft.a
LIBFT_DIR	=	./src
OBJECTS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
# FT_PRINTF
################################################################################
FT_PF_DIR	=	./ft_printf
FT_PF_OBJ	=	$(addprefix $(OBJ_DIR)/, $(FT_PF_SRC:%.c=%.o))

################################################################################
# GNL
################################################################################
GNL_DIR		=	./ft_get_next_line
GNL_OBJ		=	$(addprefix $(OBJ_DIR)/, $(GNL_SRC:%.c=%.o))

# vpath for finding source files
vpath %.c $(LIBFT_DIR) $(FT_PF_DIR) $(GNL_DIR)

all: $(NAME)

$(NAME): $(OBJECTS) $(FT_PF_OBJ) $(GNL_OBJ)
		ar -rcs $@ $^

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(@D)
		$(CC_FULL) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
