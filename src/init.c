/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:12:27 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/07 21:08:34 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_img(t_game *game)
{
	game->wall.img = mlx_new_image(game->mlx, WALL_WIDTH, WALL_HEIGHT);
	game->wall.addr = mlx_get_data_addr(game->wall.img, &game->wall.bpp, &game->wall.line_len, &game->wall.endian);
	if (!(game->wall.addr))
		 ft_put_err("Invalid wall.addr");
	game->screen.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp, &game->screen.line_len, &game->screen.endian);

	game->minimap.img = mlx_new_image(game->mlx, SCREEN_WIDTH * MINIMAP_SCALE, SCREEN_HEIGHT * MINIMAP_SCALE);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
}

static void	init_texture(t_map *map)
{
	int	fd;
	int	i;
	
	i = -1;
	while (++i < 4)
	{
		fd = open(map->tex[i].path, O_RDONLY);
		if (fd == -1)
			err(map, "Invalid .xpm File");
		close(fd);
	}
}

void	init_game(t_game *game)
{
	init_texture(game->map);
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_put_err("Invalid mlx_init");
	game->win = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->win)
		ft_put_err("Invalid mlx_win");
	init_img(game);
}
