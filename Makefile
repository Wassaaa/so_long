# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 05:08:26 by aklein            #+#    #+#              #
#    Updated: 2024/02/17 22:19:13 by aklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES		=	./include

SRCS			=	ft_lstget.c\
					anim_load.c\
					error.c\
					pixels.c\
					img_moves.c\
					map.c\
					move_it.c\
					frame_sync.c\
					animate.c\
					init.c\
					helpers.c\

B_SRCS			=


################################################################################
# COMPILATION
################################################################################
CC				=	gcc
CC_STRICT		=	-Wall -Wextra -Werror
CC_DEBUG		=	-g #-fsanitize=leak
HEADERS		=	-I $(LIBFT_INCLUDES) -I $(INCLUDES) -I $(MLX42_DIR)/include
CC_FULL			=	$(CC) $(CC_STRICT) $(HEADERS) $(CC_DEBUG)

################################################################################
# MLX
################################################################################
MLX42			= $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm 
#MLX42			= $(MLX42_DIR)/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX_DEBUG		= -DDEBUG=1
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
SRC_DIR			=	./src
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
OBJ_DIR			=	./obj
ARCHIVES		=	./archives
M_MAIN			=	./main.c
M_HEADER		=	$(INCLUDES)/so_long.h
M_ARCHIVE		=	$(ARCHIVES)/so_long.a
M_ARCHIVES		=	$(M_ARCHIVE) $(LIBFT)

################################################################################
# BONUS
################################################################################
B_NAME			= 	checker
B_DIR			=	./bonus
B_OBJECTS		=	$(addprefix $(OBJ_DIR)/, $(B_SRCS:%.c=%.o))
B_MAIN			=	./main_bonus.c
B_HEADER		=	$(INCLUDES)/push_swap_bonus.h
B_ARCHIVE		=	$(ARCHIVES)/checker.a
B_ARCHIVES		=	$(B_ARCHIVE) $(LIBFT)

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

bonus: $(B_NAME)

$(B_NAME): $(LIBFT) $(B_ARCHIVE) $(B_MAIN)
					$(CC_FULL) $(B_MAIN) $(B_ARCHIVES) -o $(B_NAME)

$(B_ARCHIVE): $(B_OBJECTS)
					mkdir -p $(@D)
					ar rcs $(B_ARCHIVE) $(B_OBJECTS)

$(OBJ_DIR)/%.o: $(B_DIR)/%.c
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
CC_VG = $(CC) $(HEADERS) $(CC_STRICT)

VG = valgrind
VG_FLAGS = --leak-check=full --show-leak-kinds=all --trace-children=yes
VG_LOG = valgrind_leaks.log
VG_LOG_FLAGS = --log-file=$(VG_LOG) \
	--leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	--track-origins=yes \
	--verbose

LOG_VG_TARGET = $(RUBY_ARGS)\
		$(VG) $(VG_LOG_FLAGS) ./push_swap $$args

VG_TARGET = $(RUBY_ARGS)\
		$(VG) $(VG_FLAGS) ./push_swap $$args

vg: vg_build
	$(VG_TARGET)

vglog: vg_build
	$(LOG_VG_TARGET)

vg_build: $(LIBFT) $(M_ARCHIVE)
	$(CC_VG) \
		$(M_MAIN) \
		$(M_ARCHIVES) \
		-o $(NAME)

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
.PHONY: all re clean fclean bonus libmlx libft_force
