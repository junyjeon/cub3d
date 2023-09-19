/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:15:07 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 21:34:31 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_game *game)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		err(map, "Map malloc failed.");
	ft_memset(map, 0, sizeof(t_map));
	game->map = map;
}

static void	init_img(t_game *g)
{
	g->screen.img = mlx_new_image(g->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!g->screen.img)
		err(g->map, "Invalid screen img");
	g->screen.data = (int *)mlx_get_data_addr(g->screen.img,
			&g->screen.bpp, &g->screen.line_len, &g->screen.endian);
	if (!g->screen.data)
		err(g->map, "Invalid screen data");
}

static void	init_mlx_win(t_game *g)
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
	g->px = g->map->player.posx;
	g->py = g->map->player.posy;
	g->dirx = g->map->player.dirx;
	g->diry = g->map->player.diry;
	g->planex = g->map->player.planex;
	g->planey = g->map->player.planey;
}

void	init(t_game *g)
{
	init_mlx_win(g);
	init_img(g);
	init_game(g);
	init_texture(g);
}
