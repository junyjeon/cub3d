/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:15:07 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/18 23:55:22 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	load_texture(t_game *g, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->width, &img->height);
	if (!img->img)
		err(g->map, "Invalid xpm file image");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
	&img->line_len, &img->endian);
	if (!img->data)
		err(g->map, "Invalid xpm file data");
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			texture[img->width * y + x] = img->data[img->width * y + x];
	}
	mlx_destroy_image(g->mlx, img->img);
}

static void	init_texture(t_game *g)
{
	t_img	image;
	int		i;

	g->texture = (int **)malloc(sizeof(int *) * 5);
	if (!g->texture)
		err(g->map, "Texture malloc failed.");
	i = -1;
	while (++i < 4)
	{
		g->texture[i] = (int *)ft_calloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
		if (!g->texture[i])
			err(g->map, "Texture malloc failed.");
		load_texture(g, g->texture[i], g->map->tex[i].path, &image);
	}
	g->texture[4] = NULL;
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
	init_mlx_win(g);
	init_img(g);
	init_game(g);
	init_texture(g);
	g->movespeed = 0.05;
	g->rotspeed = 0.05;
}
