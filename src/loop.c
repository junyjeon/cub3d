/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:14:36 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/15 20:40:58 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw(t_game *g)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_HEIGHT)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
			g->screen->
	}
}

static void	triangle_dist(t_game *g)
{
	g->mapx = (int)g->px;
	g->mapy = (int)g->py;
	(void)g->sidedistx;
	(void)g->sidedisty;

	//삼각형의 비율을 구한다. deltax의 밑변은 1이 고정이니까 높이는 x/y
	g->deltadistx = fabs(1 / g->raydirx);
	g->deltadisty = fabs(1 / g->raydiry);
	(void)g->perpwalldist; //어안렌지 방지

//x또는 y의 방향
	(void)g->stepx;
	(void)g->stepy;

	g->hit = 0; //광선이 벽에 부딪힘
	(void)g->side; // 동서? 남북?
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
		g->sidedisty = (g->px - g->mapy) * g->deltadisty;
	}
	else
	{
		g->stepy = 1;
		g->sidedisty = (g->mapy + 1.0 - g->px) * g->deltadisty;
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
			g->sidedisty += g->deltadistx;
			g->mapy += g->stepy;
			g->side = 1;
		}
		if (g->map->map[g->mapx][g->mapy] == '1')
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
	g->drawstart = -g->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (g->drawstart < 0)
		g->drawstart = 0;
	g->drawend = g->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (g->drawend >= SCREEN_HEIGHT)
		g->drawend = SCREEN_HEIGHT - 1;
	g->texnum = g->map->map[g->mapx][g->mapy];

	(void)g->wallx;
	if (g->side == 0)
		g->wallx = g->py * g->perpwalldist * g->raydiry;
	else
		g->wallx = g->px + g->perpwalldist * g->raydirx;
	
	g->texx = (int)g->wallx * (double)WALL_WIDTH;
	if (g->side == 0 && g->raydirx > 0)
		g->texx = WALL_WIDTH - g->texx - 1;
	if (g->side == 1 && g->raydiry < 0)
		g->texx = WALL_WIDTH - g->texx - 1;
}

void	other2(t_game *g, int x)
{	
	g->step = 1.0 * WALL_WIDTH / WALL_HEIGHT;
	g->texpos = (g->drawstart - SCREEN_HEIGHT / 2 + g->lineheight / 2) * g->step;
	for (int y = g->drawstart; y < g->drawend; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)g->texpos & (WALL_HEIGHT - 1);
		g->texpos += g->step;
		int color = texture[g->texnum][WALL_HEIGHT * g->texy + g->texx];
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (g->side == 1)
			color = (color >> 1) & 8355711;
		g->buf[y][x] = color;
		g->re_buf = 1;
	}
}

int	loop(t_game *g)
{
	mlx_clear_window(g->mlx, g->win);
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		g->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
		g->raydirx = g->map->player.dirx + g->map->player.planex * g->camerax;
		g->raydirx = g->map->player.diry + g->map->player.planey * g->camerax;
		draw(g);
		triangle_dist(g);
		//광선의 x가 몇분면에 있는지 찾기
		any_find(g);
		dda(g);
		prevent_fisheye_lens(g);
		other(g);
		other2(g, x);
	}
	return (0);
}