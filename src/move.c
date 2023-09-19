/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:02:30 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 21:37:59 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	moveable(t_game *game, double nx, double ny)
{
	int	x;
	int	y;

	x = (int)nx;
	y = (int)ny;
	if (x < 0 || y < 0 || x >= game->map->row || y >= game->map->col)
		return (1);
	if (game->map->map[x][y] == '1')
		return (0);
	else
		return (1);
}

static void	move(t_game *g, double angle)
{
	double	nx;
	double	ny;

	nx = g->px + (g->dirx * cos(angle) - g->diry * sin(angle)) * M_UNIT;
	ny = g->py + (g->dirx * sin(angle) + g->diry * cos(angle)) * M_UNIT;
	if (!moveable(g, nx, ny)
		|| !moveable(g, -nx + g->planex * SPEED, ny + g->planey * SPEED)
		|| !moveable(g, nx + g->planex * SPEED, ny + g->planey * SPEED)
		|| !moveable(g, -nx + g->planex * SPEED, ny - g->planey * SPEED)
		|| !moveable(g, nx + g->planex * SPEED, ny - g->planey * SPEED)
		|| !moveable(g, nx + g->planex * SPEED, -ny + g->planey * SPEED)
		|| !moveable(g, -nx + g->planex * SPEED, -ny + g->planey * SPEED)
		|| !moveable(g, nx - g->planex * SPEED, ny - g->planey * SPEED))
		return ;
	g->px = nx;
	g->py = ny;
}

static void	rotate(t_game *g, double angle)
{
	double	tempx;
	double	tempy;

	tempx = g->dirx;
	tempy = g->diry;
	g->dirx = tempx * cos(angle) - tempy * sin(angle);
	g->diry = tempx * sin(angle) + tempy * cos(angle);
	tempx = g->planex;
	tempy = g->planey;
	g->planex = tempx * cos(angle) - tempy * sin(angle);
	g->planey = tempx * sin(angle) + tempy * cos(angle);
}

void	event_rotation(t_game *g)
{
	if (g->l)
		rotate(g, R_UNIT);
	if (g->r)
		rotate(g, -R_UNIT);
}

void	event_move(t_game *g)
{
	if (g->w)
		move(g, 0);
	if (g->a)
		move(g, PI_2);
	if (g->s)
		move(g, PI);
	if (g->d)
		move(g, -PI_2);
}
