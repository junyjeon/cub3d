/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:14:36 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 23:16:54 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void draw(t_game *g)
{
	int x;
	int y;

	x = -1;
	while (++x < SCREEN_HEIGHT)
	{
		y = -1;
		while (++y < SCREEN_WIDTH)
			g->screen.data[x * SCREEN_WIDTH + y] = g->buf[x][y];
	}
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
	// mlx_put_image_to_window(g->mlx, g->win, g->.img, 0, 0); // 미니맵 띄우기
	// static int i = 0;
	// image를 (i / 20) % 5 => 반쩨 이미지.
	// mlx_put_image_to_window(g->mlx, g->win, g->hand.img, 0, 0);
} // 스프라이트 이미지
// 미니맵
//  문
//  마우스

static void find_side(t_game *g)
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

static void triangle_dist(t_game *g)
{
	g->mapx = (int)g->px;
	g->mapy = (int)g->py;
	g->deltadistx = fabs(1 / g->raydirx);
	g->deltadisty = fabs(1 / g->raydiry);
	g->hit = 0;
}

static void update_state(t_game *g)
{
	if (g->w || g->a || g->s || g->d)
		event_move(g);
	if (g->l || g->r)
		event_rotation(g);
}

int loop(t_game *g)
{
	int x;

	update_state(g);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		g->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
		g->raydirx = g->dirx + g->planex * g->camerax;
		g->raydiry = g->diry + g->planey * g->camerax;
		triangle_dist(g);
		find_side(g);
		dda(g);
		prevent_fisheye_lens(g);
		calc_wall(g);
		set_vertical_line(g, x);
	}
	draw(g);
	return (0);
}
