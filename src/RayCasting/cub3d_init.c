/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:09:42 by gshim             #+#    #+#             */
/*   Updated: 2023/09/11 03:03:11 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	game_init(t_game *g)
{
	double	angle;

	g->w = false;
	g->a = false;
	g->s = false;
	g->d = false;
	g->l = false;
	g->r = false;
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

int	window_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		err(game->map, "Invalid mlx_init");
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB_3D");
	if (!game->win)
		err(game->map, "Invalid win_init");
	return (0);
}

static void	texture_init(t_game *g)
{
	t_texture	*tx;
	int			i;

	tx = g->map->tex;
	i = -1;
	while (++i < 4)
	{
		//Todo. 텍스쳐 addr, texture[][]배열이 필요한지 체크
		tx[i].texture.img = mlx_xpm_file_to_image(g->mlx,\
		tx[i].path, &(tx[i].width), &(tx[i].height));
		if (!tx[i].texture.img)
			err(g->map, "Invalid texture.img");
		tx[i].texture.data = mlx_get_data_addr(tx[i].texture.img,\
		&(tx[i].texture.bpp), &(tx[i].texture.line_len), &(tx[i].texture.endian));
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
	g->screen.data = (unsigned int*)mlx_get_data_addr(g->screen.img,
			&(g->screen.bpp), &(g->screen.line_len), &(g->screen.endian));
	g->minimap.img = mlx_new_image(g->mlx, g->miniw, g->minih);
	g->minimap.data = (unsigned int*)mlx_get_data_addr(g->minimap.img,
			&(g->minimap.bpp), &(g->minimap.line_len), &(g->minimap.endian));
}
