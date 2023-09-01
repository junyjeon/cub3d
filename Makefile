# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 19:23:49 by junyojeo          #+#    #+#              #
#    Updated: 2023/09/01 21:00:18 by junyojeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS		+=	-fsanitize=thread

INC_DIR		=	./inc

LIBFT_DIR	=	./lib/libft
LIBFT_AC	=	$(LIBFT_DIR)/libft.a

GNL_DIR		=	./lib/get_next_line
GNL_AC		=	$(GNL_DIR)/get_next_line.a

MLX_DIR		=	./lib/minilibx_opengl_20191021
MLX_AC		=	$(MLX_DIR)/libmlx.a
MLX_LNK		=	-framework OpenGL -framework AppKit

CPPFLAGS	=	-I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		=	-L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -L$(MLX_DIR) -lmlx

SRC_DIR		=	src
BUILD_DIR	=	bulid

SRC		=	$(addprefix $(SRC_DIR)/, main.c \
			error/error.c \
			parsing/parse_color.c \
			parsing/parse_map.c \
			parsing/map_setting.c \
			parsing/parse.c \
			parsing/validation.c \
			utils/util.c \
			raycasting/cub3d_init.c \
			raycasting/deal_key.c \
			raycasting/ray_cal.c \
			raycasting/ray_render.c \
			raycasting/move.c \

OBJ		=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all:	$(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(MLX_LNK)
	@echo "$(GREEN)SUCCESS!$(END)"

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@$(RM) -r $(BUILD_DIR)

fclean: clean
	@$(RM) -r $(NAME)
	@echo "${YELLOW}> Cleaning of the cub3D has been done.❌${END}"

re: fclean all

Yellow : \033[0;33m
Green  : \033[0;32m

.PHONY: all clean fclean re
