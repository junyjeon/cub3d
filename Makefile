# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 19:23:49 by junyojeo          #+#    #+#              #
#    Updated: 2023/09/03 02:08:56 by junyojeo         ###   ########.fr        #
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
			parse/parse_color.c \
			parse/parse_map.c \
			parse/map_setting.c \
			parse/parse.c \
			parse/validation.c \
			utils/util.c \
			ray/cub3d_init.c \
			ray/deal_key.c \
			ray/ray_cal.c \
			ray/ray_render.c \
			ray/move.c \

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
