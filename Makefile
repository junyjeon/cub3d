# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 19:23:49 by junyojeo          #+#    #+#              #
#    Updated: 2023/09/20 03:37:58 by junyojeo         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-fsanitize=address
CFLAGS		+=	-g3 --pedantic

INC_DIR		=	./inc

LIBFT_DIR	=	./lib/libft
LIBFT_AC	=	$(LIBFT_DIR)/libft.a

GNL_DIR		=	./lib/get_next_line
GNL_AC		=	$(GNL_DIR)/libGNL.a

MLX_DIR		=	./lib/minilibx_opengl_20191021
MLX_AC		=	$(MLX_DIR)/libmlx.a
MLX_LNK		=	-framework OpenGL -framework AppKit

CPPFLAGS	=	-I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		=	-L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lGNL -L$(MLX_DIR) -lmlx

SRC_DIR		=	src
BUILD_DIR	=	build

SRC		=	$(addprefix $(SRC_DIR)/, main.c parse.c parse_map.c parse_main.c dfs.c key_hook.c key_event.c loop.c loop2.c init.c texture.c move.c utils.c)

OBJ		=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all:	$(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR) bonus
	@make -C $(GNL_DIR)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(MLX_LNK)
	@echo "$(GREEN)SUCCESS!$(END)"

$(LIBFT_AC):	
	@make -C $(LIBFT_DIR) bonus

$(GNL_AC):
	@make -C $(GNL_DIR)

$(MLX_AC):
	@make -C $(MLX_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@$(RM) -r $(BUILD_DIR)

fclean: clean
	@$(RM) -r $(NAME) $(LIBFT_AC) $(GNL_AC) $(MLX_AC)
	@echo "${YELLOW}> Cleaning of the cub3D has been done.❌${END}"

re: fclean all

Yellow : \033[0;33m
Green  : \033[0;32m

.PHONY: all clean fclean re
