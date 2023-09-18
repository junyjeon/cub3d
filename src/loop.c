/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:14:36 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/18 21:03:17 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			g->screen.data[y * SCREEN_WIDTH + x] = g->buf[y][x]; 
	}
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
}

static void	triangle_dist(t_game *g)
{
	g->mapx = (int)g->px;
	g->mapy = (int)g->py;

	//삼각형의 비율을 구한다. deltax의 밑변은 1이 고정이니까 높이는 x/y
	g->deltadistx = fabs(1 / g->raydirx);
	g->deltadisty = fabs(1 / g->raydiry);

	g->hit = 0; //광선이 벽에 부딪힘
}

static void	any_find(t_game *g)
{
	if (g->raydirx < 0)
	{
		g->stepx = -1;
		g->sidedistx = (g->px - g->mapx) * g->deltadistx;
	}
	else
	{
		g->stepx = 1;
		g->sidedistx = (g->mapx + 1.0 - g->px) * g->deltadistx;
	}
	if (g->raydiry < 0)
	{
		g->stepy = -1;
		g->sidedisty = (g->py - g->mapy) * g->deltadisty;
	}
	else
	{
		g->stepy = 1;
		g->sidedisty = (g->mapy + 1.0 - g->py) * g->deltadisty;
	}
}
//Todo. 다시 이해하기
static void	dda(t_game *g)
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
		if (g->map->map[g->mapx][g->mapy] > '0')
			g->hit = 1;
	}
}

void	prevent_fisheye_lens(t_game *g)
{
	if (g->side == 0)
		g->perpwalldist = (g->mapx - g->px + (1 - g->stepx) / 2) / g->raydirx;
	else
		g->perpwalldist = (g->mapy - g->py + (1 - g->stepy) / 2) / g->raydiry;
}

void	other(t_game *g)
{
	g->lineheight = (int)(SCREEN_HEIGHT / g->perpwalldist);

	g->drawstart = -(g->lineheight) / 2 + SCREEN_HEIGHT / 2;
	if (g->drawstart < 0)
		g->drawstart = 0;
	g->drawend = g->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (g->drawend >= SCREEN_HEIGHT)
		g->drawend = SCREEN_HEIGHT - 1;

	g->texnum = g->map->map[g->mapx][g->mapy];

	if (g->side == 0)
		g->wallx = g->py * g->perpwalldist * g->raydiry;
	else
		g->wallx = g->px + g->perpwalldist * g->raydirx;
	g->wallx -= floor(g->wallx);
	
	g->texx = (int)g->wallx * (double)TEX_WIDTH;
	if (g->side == 0 && g->raydirx > 0)
		g->texx = TEX_WIDTH - g->texx - 1;
	if (g->side == 1 && g->raydiry < 0)
		g->texx = TEX_WIDTH - g->texx - 1;
}

void	other2(t_game *g, int x)
{	
	g->step = 1.0 * TEX_HEIGHT / g->lineheight;
	g->texpos = (g->drawstart - SCREEN_HEIGHT / 2 + g->lineheight / 2) * g->step;
	for (int y = g->drawstart; y < g->drawend; y++)
	{
		g->texy = (int)g->texpos & (TEX_HEIGHT - 1);
		g->texpos += g->step;
		g->color = g->texture[g->texnum][TEX_HEIGHT * g->texy + g->texx];
		if (g->side == 1)
			g->color = (g->color >> 1) & 8355711;
		g->buf[y][x] = g->color;
		g->re_buf = 1;
	}
}

int	loop(t_game *g)
{
	int	x;

	for (int i = 0; i < SCREEN_HEIGHT; i++)
		for (int j = 0; j < SCREEN_WIDTH; j++)
			g->buf[i][j] = 0xFFFF00;
	// ft_memset(g->buf, 0, sizeof(g->buf));
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		g->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
		g->raydirx = g->dirx + g->planex * g->camerax;
		g->raydiry = g->diry + g->planey * g->camerax;
		triangle_dist(g);
		//광선의 x가 몇분면에 있는지 찾기
		any_find(g);
		dda(g);
		prevent_fisheye_lens(g);
		other(g);
		other2(g, x);
	}
	draw(g);
	return (0);
}