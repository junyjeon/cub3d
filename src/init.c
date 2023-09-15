/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:15:07 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/15 18:17:59 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


static void	init_texture(t_game *g)
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
		tx[i].texture.data = (unsigned int*)mlx_get_data_addr(tx[i].texture.img,\
		&(tx[i].texture.bpp), &(tx[i].texture.line_len), &(tx[i].texture.endian));
		if (tx[i].path)
		{
			free(tx[i].path);
			tx[i].path = NULL;
		}
	}
}

static void	init_img(t_game *g)
{
	g->screen.img = mlx_new_image(g->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	g->screen.data = (unsigned int*)mlx_get_data_addr(g->screen.img,
			&(g->screen.bpp), &(g->screen.line_len), &(g->screen.endian));
	g->minimap.img = mlx_new_image(g->mlx, g->miniw, g->minih);
	g->minimap.data = (unsigned int*)mlx_get_data_addr(g->minimap.img,
			&(g->minimap.bpp), &(g->minimap.line_len), &(g->minimap.endian));
}

static void	init_win(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		err(g->map, "Invalid mlx_init");
	g->win = mlx_new_window(g->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB_3D");
	if (!g->win)
		err(g->map, "Invalid win_init");
}


static void	init_game(t_game *g)
{
	g->w = false;
	g->a = false;
	g->s = false;
	g->d = false;
	g->l = false;
	g->r = false;
	g->minih = SCREEN_WIDTH * MINIMAP_SCALE;
	g->miniw = SCREEN_HEIGHT * MINIMAP_SCALE;
	g->px = g->map->player.posx;
	g->py = g->map->player.posy;
	g->dirx = g->map->player.dirx;
	g->diry = g->map->player.diry;
	g->planex = g->map->player.planex; 
	g->planey = g->map->player.planey;
}

void	init(t_game *g)
{
	init_game(g);
	init_win(g);
	init_img(g);
	init_texture(g);
}