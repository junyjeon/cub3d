/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:09:42 by gshim             #+#    #+#             */
/*   Updated: 2023/09/10 03:53:30 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	game_init(t_game *g)
{
	double	angle;

	g->px = g->map->player.posx;
	g->py = g->map->player.posy;
	if (g->map->player.start_sight == 'N')
		angle = M_PI;
	else if (g->map->player.start_sight == 'E')
		angle = M_PI_2;
	else if (g->map->player.start_sight == 'S')
		angle = 0;
	else
		angle = -M_PI_2;
	g->dirx = cos(angle);
	g->diry = sin(angle);
	g->planex = 0.66 * cos(angle - M_PI_2);
	g->planey = 0.66 * sin(angle - M_PI_2);
	g->miniw = SCREEN_WIDTH * MINIMAP_SCALE;
	g->minih = SCREEN_HEIGHT * MINIMAP_SCALE;
	g->gridw = g->miniw / g->map->col;
	g->gridh = g->minih / g->map->row;
	g->mousemode = 0;
}

static void	texture_init(t_game *g)
{
	t_texture	*tx;
	int			i;

	tx = g->map->tex;
	tx[0].texture.img = mlx_xpm_file_to_image(g->mlx,
			tx[0].path, &(tx[0].width), &(tx[0].height));
	tx[1].texture.img = mlx_xpm_file_to_image(g->mlx,
			tx[1].path, &(tx[1].width), &(tx[1].height));
	tx[2].texture.img = mlx_xpm_file_to_image(g->mlx,
			tx[2].path, &(tx[2].width), &(tx[2].height));
	tx[3].texture.img = mlx_xpm_file_to_image(g->mlx,
			tx[3].path, &(tx[3].width), &(tx[3].height));
	i = -1;
	while (++i < 4)
	{
		if (tx[i].path)
		{
			free(tx[i].path);
			tx[i].path = NULL;
		}
	}
}

void	img_init(t_game *g)
{
	texture_init(g);
	g->screen.img = mlx_new_image(g->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	g->screen.addr = mlx_get_data_addr(g->screen.img,
			&(g->screen.bpp), &(g->screen.line_len), &(g->screen.endian));
	g->minimap.img = mlx_new_image(g->mlx, g->miniw, g->minih);
	g->minimap.addr = mlx_get_data_addr(g->minimap.img,
			&(g->minimap.bpp), &(g->minimap.line_len), &(g->minimap.endian));
}
#include "stdio.h"

int	window_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		err(game->map, "Invalid mlx_init");
	//여기서 세그폴트가 왜 나?
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB_3D");
	if (!game->win)
		err(game->map, "Invalid win_init");
	return (0);
}
