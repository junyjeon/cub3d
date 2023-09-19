/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:58:42 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 21:32:43 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	prevent_fisheye_lens(t_game *g)
{
	if (g->side == 0)
		g->perpwalldist = (g->mapx - g->px + (1 - g->stepx) / 2) / g->raydirx;
	else
		g->perpwalldist = (g->mapy - g->py + (1 - g->stepy) / 2) / g->raydiry;
}

void	calc_wall(t_game *g)
{
	g->lineheight = (int)(SCREEN_HEIGHT / g->perpwalldist);
	g->drawstart = -g->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (g->drawstart < 0)
		g->drawstart = 0;
	g->drawend = g->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (g->drawend >= SCREEN_HEIGHT)
		g->drawend = SCREEN_HEIGHT - 1;
	g->texnum = g->map->map[g->mapx][g->mapy] - '0';
	if (g->side == 0)
		g->wallx = g->py + g->perpwalldist * g->raydiry;
	else
		g->wallx = g->px + g->perpwalldist * g->raydirx;
	g->wallx -= floor(g->wallx);
	g->texx = (int)(g->wallx * (double)TEX_WIDTH);
	if (g->side == 0 && g->raydirx > 0)
		g->texx = TEX_WIDTH - g->texx - 1;
	if (g->side == 1 && g->raydiry < 0)
		g->texx = TEX_WIDTH - g->texx - 1;
	g->step = 1.0 * TEX_HEIGHT / g->lineheight;
	g->texpos = (g->drawstart - SCREEN_HEIGHT / 2 + g->lineheight / 2) \
	* g->step;
}

void	set_vertical_line(t_game *g, int x)
{
	int	y;

	y = -1;
	while (++y < g->drawstart)
		g->buf[y][x] = g->map->color_ceil;
	y = g->drawstart;
	while (++y < g->drawend)
	{
		g->texy = (int)g->texpos & (TEX_HEIGHT - 1);
		g->texpos += g->step;
		g->color = g->texture[g->texnum][TEX_WIDTH * g->texy + g->texx];
		if (g->side == 1)
			g->color = (g->color >> 1) & 8355711;
		g->buf[y][x] = g->color;
		g->re_buf = 1;
	}
	y = g->drawend;
	while (++y < SCREEN_HEIGHT)
		g->buf[y][x] = g->map->color_floor;
}

void	dda(t_game *g)
{
	while (g->hit == 0)
	{
		if (g->sidedistx < g->sidedisty)
		{
			g->sidedistx += g->deltadistx;
			g->mapx += g->stepx;
			g->side = 0;
		}
		else
		{
			g->sidedisty += g->deltadisty;
			g->mapy += g->stepy;
			g->side = 1;
		}
		if (g->map->map[g->mapx][g->mapy] == '1')
			g->hit = 1;
	}
}
