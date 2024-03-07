# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 05:08:26 by aklein            #+#    #+#              #
#    Updated: 2024/03/07 20:40:12 by aklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	\
					anim.c\
					anim_utils.c\
					display.c\
					draw_entity.c\
					draw_tiles.c\
					draw.c\
					error_utils.c\
					error.c\
					frame_sync.c\
					ft_lstget.c\
					game_ui.c\
					gun.c\
					helpers.c\
					img_edit.c\
					init.c\
					load_png.c\
					load_utils.c\
					map_read.c\
					map.c\
					move_enemy.c\
					move_helpers.c\
					move_image.c\
					move_player.c\
					move.c\
					number_display.c\
					pixels.c\
					pixels_alpha_blend.c\
					pixels_utils.c\
					sizes.c\

################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
OFAST			=	#-Ofast -flto
OG				=	#-Og -flto
CC_DEBUG		=	-g #-fsanitize=leak
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES) -I $(MLX42_DIR)/include
CC_FULL			=	$(CC) $(CC_STRICT) $(HEADERS) $(CC_DEBUG) $(OG) $(OFAST)

################################################################################
# MLX
################################################################################
#MLX42			= $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX42			= $(MLX42_DIR)/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX_DEBUG		= #-DDEBUG=1
MLX42_DIR		= ./MLX42

################################################################################
# LIBFT
################################################################################
LIBFT			=	./libft/libft.a
LIBFT_DIR		=	./libft
LIBFT_INCLUDES	=	./libft/include

################################################################################
# MANDATORY
################################################################################
NAME			=	so_long
INCLUDES		=	./include
SRC_DIR			=	./src
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
OBJ_DIR			=	./obj
ARCHIVES		=	./archives
M_MAIN			=	./main.c
M_HEADER		=	$(INCLUDES)/so_long.h
M_ARCHIVE		=	$(ARCHIVES)/so_long.a
M_ARCHIVES		=	$(M_ARCHIVE) $(LIBFT)

################################################################################
# RULES
################################################################################

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX42_DIR) $(MLX_DEBUG) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

$(NAME): $(LIBFT) $(M_ARCHIVE) $(M_MAIN)
	$(CC_FULL) $(M_MAIN) $(M_ARCHIVES) $(MLX42) -o $(NAME)

$(LIBFT): libft_force
	make -C $(LIBFT_DIR)

libft_force:
	@true

$(M_ARCHIVE): $(OBJECTS)
	mkdir -p $(@D)
	ar rcs $(M_ARCHIVE) $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(M_HEADER)
	mkdir -p $(@D)
	$(CC_FULL) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(ARCHIVES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(B_NAME)
	make fclean -C $(LIBFT_DIR)
	rm -rf $(MLX42_DIR)/build

re: fclean all

################################################################################
# TESTING
################################################################################

################################################################################
# VALGRIND
################################################################################
CC_VG			=	$(CC) $(CC_STRICT) $(HEADERS)

VG				=	valgrind
VG_ARGS			=	#
VG_FLAGS		=	--leak-check=full --show-leak-kinds=all --suppressions=suppressions
VG_LOG			=	valgrind_leaks.log
VG_LOG_FLAGS	=	--log-file=$(VG_LOG) \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes \
					--verbose \
					--suppressions=suppressions \
					--gen-suppressions=all

LOG_VG_TARGET	=	$(VG) $(VG_LOG_FLAGS) ./$(NAME) $(VG_ARGS)

VG_TARGET		=	$(VG) $(VG_FLAGS) ./$(NAME) $(VG_ARGS)

vg: vg_build
	$(VG_TARGET)

vglog: vg_build
	$(LOG_VG_TARGET)

vg_build: libmlx $(LIBFT) $(M_ARCHIVE)
	$(CC_VG) $(M_MAIN) $(M_ARCHIVES) $(MLX42) -o $(NAME)

vglog_clean: fclean
	rm -f $(VG_LOG)

################################################################################
# NORM
################################################################################
norm:
	norminette $(SRC_DIR) $(B_DIR) $(INCLUDES) $(LIBFT_DIR) | grep -v "OK!" || true

norm2:
	norminette $(SRC_DIR) $(B_DIR) $(INCLUDES) $(LIBFT_DIR)

################################################################################
# Colors
################################################################################
# Black, Red, Green, Yellow, Blue, Purple, Cyan, White
BK = \033[0;30m
R = \033[0;31m
G = \033[0;32m
Y = \033[0;33m
B = \033[0;34m
P = \033[0;35m
C = \033[0;36m
W = \033[0;37m
# Bold
BKB = \033[1;30m
RB = \033[1;31m
GB = \033[1;32m
YB = \033[1;33m
BB = \033[1;34m
PB = \033[1;35m
CB = \033[1;36m
WB = \033[1;37m
# Reset Color
RC = \033[0m

################################################################################
# PHONY
################################################################################
.PHONY: all re clean fclean libmlx libft_force
