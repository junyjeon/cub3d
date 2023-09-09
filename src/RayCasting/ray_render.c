/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:38:16 by gshim             #+#    #+#             */
/*   Updated: 2023/09/10 03:24:21 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cast_one_ray(t_game *g, int x)
{
	t_texture		wall_tex;

	ray_cal_init(g, x);
	getsidedist(g);
	dda(g);
	getdrawpoint(g);
	wall_tex = getwalltexture(g);
	wall_tex.data = (unsigned int *)mlx_get_data_addr(wall_tex.texture.img,
			&wall_tex.texture.bpp, (int *)wall_tex.texture.addr,
			&wall_tex.texture.endian);
	cal_texture(g, &wall_tex);
	drawline(g, &wall_tex, x);
}

void	drawline(t_game *g, t_texture *wall_tex, int x)
{
	int	color;
	int	y;

	y = g->drawstart - 1;
	while (++y < g->drawend)
	{
		g->texy = (int)(g->texpos) & (wall_tex->height - 1);
		g->texpos += g->step;
		color = wall_tex->data[wall_tex->height * g->texy + g->texx];
		if (g->side == 1)
			color = (color >> 1) & 8355711;
		g->screen.addr[y * SCREEN_WIDTH + x] = color;
	}
}

void	setscreen(t_game *g)
{
	int	y;
	int	x;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			if (y <= SCREEN_HEIGHT / 2)
				g->screen.addr[y * SCREEN_WIDTH + x] = g->map->ceil_color;
			else if (y > SCREEN_HEIGHT / 2)
				g->screen.addr[y * SCREEN_WIDTH + x] = g->map->floor_color;
		}
	}
}

// W E N S
t_texture	getwalltexture(t_game *g)
{
	if (g->side == 0)
	{
		if (g->stepx == -1)
			return (g->map->tex[2]);
		else
			return (g->map->tex[3]);
	}
	else
	{
		if (g->stepy == -1)
			return (g->map->tex[0]);
		else
			return (g->map->tex[1]);
	}
}
